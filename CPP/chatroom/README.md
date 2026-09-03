# CalcWarrior Chat

一个轻量级局域网聊天室，C++ 后端 + Web 前端，浏览器即可使用。

## 特性

- 局域网内实时聊天，无需互联网
- 浏览器访问，无需安装任何客户端
- 实时消息推送（WebSocket）
- 在线用户列表
- 深色主题界面
- 单 exe 运行，零依赖
- 设计预留外网扩展接口

## 快速开始

```
1. 下载 CalcWarrior-Chat.zip 并解压
2. 双击 run.bat
3. 浏览器自动打开 http://localhost:8080
```

同一局域网内的其他设备，访问 `http://你的IP:8080` 即可加入聊天。

## 手动构建

需要 MinGW-w64 (g++) 编译环境。

```bash
cd CPP/chatroom
g++ -std=c++11 -O2 -static server.cpp -o server.exe -lws2_32 -lpthread
```

或双击 `build.bat` 一键构建。

## 项目结构

```
CalcWarriorChat/
├── server.exe          # 服务器程序
├── run.bat             # 启动脚本（双击运行）
├── public/
│   └── index.html      # 前端页面
└── 源码文件（非运行必需）：
    ├── server.cpp      # 服务器源码
    ├── config.h        # 配置文件
    ├── httplib.h       # HTTP/WebSocket 库
    ├── build.bat       # 构建脚本
    └── cert/           # SSL 证书目录（预留）
```

## 消息协议

基于 WebSocket，JSON 格式：

**客户端 → 服务器：**
```json
{"type": "chat", "msg": "你好"}
{"type": "set_name", "name": "韦先生"}
```

**服务器 → 所有客户端：**
```json
{"type": "chat", "name": "韦先生", "msg": "你好"}
{"type": "join", "name": "韦先生"}
{"type": "leave", "name": "韦先生"}
{"type": "system", "msg": "欢迎加入"}
```

## 外网部署

`config.h` 中集中管理网络参数，支持以下方案：

| 方案 | 改动 | 说明 |
|---|---|---|
| Tailscale | 改 HOST 为 Tailscale IP | 虚拟组网，免费 |
| VPS | 上传至 Linux 服务器编译运行 | 需公网 IP |
| Cloudflare Tunnel | 本机运行 cloudflared | 无需公网 IP |
