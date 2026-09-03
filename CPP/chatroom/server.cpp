// server.cpp — CalcWarrior 加密聊天室服务端
// 端到端加密：服务器只转发密文，不持有密钥
// 编译：g++ -std=c++17 -O2 server.cpp crypto_utils.cpp -o server.exe
//       -I D:/msys64/ucrt64/include -L D:/msys64/ucrt64/lib -lsodium -lws2_32

#include "httplib.h"
#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <map>
#include <windows.h>

using httplib::ws::WebSocket;
using httplib::ws::ReadResult;

// ========== 数据结构 ==========

struct Client {
    WebSocket* ws;
    std::string name;
};

struct Room {
    std::string name;
    std::vector<Client*> members;
};

std::map<std::string, Room> rooms;
std::mutex mtx;

// ========== JSON 工具 ==========

std::string j_esc(const std::string& s) {
    std::string o; o.reserve(s.size());
    for (char c : s) {
        switch (c) {
            case '"': o += "\\\""; break;
            case '\\': o += "\\\\"; break;
            case '\n': o += "\\n";  break;
            case '\r': o += "\\r";  break;
            case '\t': o += "\\t";  break;
            default:   o += c;
        }
    }
    return o;
}

std::string j_get(const std::string& j, const std::string& f) {
    std::string k = "\"" + f + "\":\"";
    auto p = j.find(k);
    if (p == std::string::npos) return "";
    p += k.size();
    std::string v;
    while (p < j.size() && j[p] != '"') {
        if (j[p] == '\\' && p+1 < j.size()) p++;
        v += j[p++];
    }
    return v;
}

// ========== 广播 ==========

void broadcast_text(const std::string& room, const std::string& msg, WebSocket* excl = nullptr) {
    std::lock_guard<std::mutex> lk(mtx);
    auto it = rooms.find(room);
    if (it == rooms.end()) return;
    for (auto* c : it->second.members)
        if (c->ws != excl) c->ws->send(msg);  // send(string) → Text frame
}

void broadcast_bin(const std::string& room, const std::string& data, WebSocket* excl = nullptr) {
    std::lock_guard<std::mutex> lk(mtx);
    auto it = rooms.find(room);
    if (it == rooms.end()) return;
    for (auto* c : it->second.members)
        if (c->ws != excl) c->ws->send(data.data(), data.size());  // send(char*,len) → Binary frame
}

std::string userlist_json(const std::string& room) {
    std::lock_guard<std::mutex> lk(mtx);
    auto it = rooms.find(room);
    if (it == rooms.end()) return R"("users":[])";
    std::string j = R"("users":[)";
    for (size_t i = 0; i < it->second.members.size(); i++) {
        if (i) j += ",";
        j += "\"" + j_esc(it->second.members[i]->name) + "\"";
    }
    j += "]";
    return j;
}

void push_userlist(const std::string& room) {
    broadcast_text(room, "{\"type\":\"system\",\"msg\":\"users updated\"," + userlist_json(room) + "}");
}

// ========== 消息处理（仅处理服务器需要知道的文本帧） ==========

void handle_text(WebSocket* ws, const std::string& raw, Client* me, std::string& my_room) {
    std::string type = j_get(raw, "type");

    if (type == "join") {
        std::string name = j_get(raw, "name");
        std::string room = j_get(raw, "room");
        if (name.empty()) return;
        if (room.empty()) room = "lobby";

        // 从旧房间移除（不 delete，只移动指针）
        {
            std::lock_guard<std::mutex> lk(mtx);
            for (auto& [rn, r] : rooms) {
                for (auto it = r.members.begin(); it != r.members.end(); ++it) {
                    if ((*it)->ws == ws) { r.members.erase(it); break; }
                }
            }
            rooms[room].name = room;
            rooms[room].members.push_back(me);
            me->name = name;
            my_room = room;
        }
        std::cerr << "[+] " << name << " → 房间 " << room << std::endl;
        broadcast_text(room, "{\"type\":\"join\",\"name\":\"" + j_esc(name) + "\"," + userlist_json(room) + "}");
    }
    else if (type == "set_name") {
        std::string nn = j_get(raw, "name");
        if (nn.empty()) return;
        me->name = nn;
        push_userlist(my_room);
    }
}

// ========== WebSocket 连接 ==========

void on_ws_connect(const httplib::Request& req, WebSocket& ws) {
    std::cerr << "[+] " << req.remote_addr << std::endl;

    Client* me = new Client{&ws, ""};
    std::string my_room = "lobby";
    {
        std::lock_guard<std::mutex> lk(mtx);
        rooms["lobby"].name = "lobby";
        rooms["lobby"].members.push_back(me);
    }

    std::string msg;
    ReadResult rr;
    while (true) {
        rr = ws.read(msg);
        if (rr == ReadResult::Text) {
            handle_text(&ws, msg, me, my_room);
        } else if (rr == ReadResult::Binary) {
            // 二进制帧 = 加密内容，服务器不解密，直接转发
            broadcast_bin(my_room, msg, &ws);
        } else {
            break;  // Fail
        }
    }

    // 断开清理
    std::string dn;
    {
        std::lock_guard<std::mutex> lk(mtx);
        for (auto& [rn, r] : rooms) {
            for (auto it = r.members.begin(); it != r.members.end(); ++it) {
                if ((*it)->ws == &ws) { dn = (*it)->name; my_room = rn; delete *it; r.members.erase(it); break; }
            }
        }
    }
    if (!dn.empty()) {
        std::cerr << "[-] " << dn << std::endl;
        broadcast_text(my_room, "{\"type\":\"leave\",\"name\":\"" + j_esc(dn) + "\"," + userlist_json(my_room) + "}");
    }
}

// ========== main ==========

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cerr << "=== CalcWarrior 加密聊天 ===" << std::endl;
    std::cerr << Config::HOST << ":" << Config::PORT << std::endl;
    std::cerr << "服务器不持有密钥，只转发密文" << std::endl << std::endl;

    httplib::Server svr;
    svr.set_mount_point("/", "public");
    svr.WebSocket("/ws", on_ws_connect);
    svr.set_logger([](const httplib::Request& r, const httplib::Response& res) {
        std::cerr << r.method << " " << r.path << " → " << res.status << std::endl;
    });
    std::cerr << "就绪 → http://localhost:" << Config::PORT << std::endl;
    svr.listen(Config::HOST, Config::PORT);
    return 0;
}
