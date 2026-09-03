// config.h — 网络参数集中配置
// 所有网络相关常量放这里，换外网方案只改此文件
#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    static constexpr const char* HOST = "0.0.0.0";     // 监听地址（0.0.0.0 = 所有网卡）
    static constexpr int PORT = 8080;                   // 服务端口
    static constexpr const char* CERT_FILE = "cert/server.crt";  // SSL 证书（暂未启用）
    static constexpr const char* KEY_FILE = "cert/server.key";   // SSL 私钥（暂未启用）

    // ---- 外网扩展方案（不改代码，只改 HOST） ----
    // Tailscale:   HOST = "100.x.x.x"（虚拟组网 IP）
    // VPS 部署:    上传到 Linux，HOST = "0.0.0.0" 或公网 IP
    // Cloudflare:  本机跑 cloudflared tunnel，HOST 保持 "0.0.0.0"

    // ---- AI 服务（Python ai_service.py） ----
    static constexpr const char* AI_HOST = "127.0.0.1";
    static constexpr int AI_PORT = 5005;
    static constexpr int AI_TIMEOUT_SEC = 30;   // AI 回复超时（秒）
};

// SSL 暂未启用（OpenSSL DLL 路径问题），纯 HTTP + ws:// 局域网内无安全风险

#endif
