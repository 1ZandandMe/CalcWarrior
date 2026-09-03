// crypto_utils.cpp — libsodium 加密工具实现
#include "crypto_utils.h"
#include <sodium.h>
#include <fstream>
#include <cstring>

static bool sodium_ready = []() {
    return sodium_init() >= 0;
}();

// ========== 密钥派生 ==========

bool derive_key(const std::string& password, uint8_t key_out[32]) {
    if (!sodium_ready || password.empty()) return false;
    return crypto_pwhash(key_out, crypto_secretbox_KEYBYTES,
                         password.c_str(), password.size(),
                         nullptr,  // salt=nullptr → 库内部随机生成
                         crypto_pwhash_OPSLIMIT_INTERACTIVE,
                         crypto_pwhash_MEMLIMIT_INTERACTIVE,
                         crypto_pwhash_ALG_ARGON2ID13) == 0;
}

// ========== 消息加解密 ==========

std::vector<uint8_t> msg_encrypt(const std::vector<uint8_t>& plain, const uint8_t key[32]) {
    if (!sodium_ready || plain.empty()) return {};

    std::vector<uint8_t> packet(crypto_secretbox_NONCEBYTES + plain.size() + crypto_secretbox_MACBYTES);
    uint8_t* nonce  = packet.data();
    uint8_t* cipher = packet.data() + crypto_secretbox_NONCEBYTES;

    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    crypto_secretbox_easy(cipher, plain.data(), plain.size(), nonce, key);
    return packet;
}

std::vector<uint8_t> msg_decrypt(const std::vector<uint8_t>& packet, const uint8_t key[32]) {
    if (!sodium_ready || packet.size() < crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES)
        return {};

    const uint8_t* nonce  = packet.data();
    const uint8_t* cipher = packet.data() + crypto_secretbox_NONCEBYTES;
    size_t cipher_len     = packet.size() - crypto_secretbox_NONCEBYTES;

    std::vector<uint8_t> plain(cipher_len - crypto_secretbox_MACBYTES);
    if (crypto_secretbox_open_easy(plain.data(), cipher, cipher_len, nonce, key) != 0)
        return {};  // MAC 验证失败 = 密码错误/数据被篡改

    return plain;
}

std::vector<uint8_t> msg_encrypt(const std::string& plain, const uint8_t key[32]) {
    return msg_encrypt(std::vector<uint8_t>(plain.begin(), plain.end()), key);
}

std::string msg_decrypt_to_string(const std::vector<uint8_t>& packet, const uint8_t key[32]) {
    auto plain = msg_decrypt(packet, key);
    if (plain.empty()) return {};
    return std::string(plain.begin(), plain.end());
}

// ========== 文件加解密 ==========

std::vector<uint8_t> file_encrypt(const std::string& file_path, const uint8_t key[32]) {
    if (!sodium_ready) return {};

    // 提取文件名
    auto pos = file_path.find_last_of("/\\");
    std::string fname = (pos != std::string::npos) ? file_path.substr(pos + 1) : file_path;

    std::ifstream in(file_path, std::ios::binary | std::ios::ate);
    if (!in) return {};
    size_t fsize = in.tellg();
    in.seekg(0, std::ios::beg);
    std::vector<uint8_t> raw(fsize);
    in.read(reinterpret_cast<char*>(raw.data()), fsize);

    // 格式: salt(16) | name_len(2) | filename | nonce(24) | ciphertext
    size_t hdr = crypto_pwhash_SALTBYTES + 2 + fname.size();
    size_t enc = crypto_secretbox_NONCEBYTES + raw.size() + crypto_secretbox_MACBYTES;
    std::vector<uint8_t> out(hdr + enc);

    randombytes_buf(out.data(), crypto_pwhash_SALTBYTES);
    uint16_t nl = static_cast<uint16_t>(fname.size());
    memcpy(out.data() + crypto_pwhash_SALTBYTES, &nl, 2);
    memcpy(out.data() + crypto_pwhash_SALTBYTES + 2, fname.c_str(), fname.size());

    uint8_t* nonce  = out.data() + hdr;
    uint8_t* cipher = nonce + crypto_secretbox_NONCEBYTES;
    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    crypto_secretbox_easy(cipher, raw.data(), raw.size(), nonce, key);
    return out;
}

bool file_decrypt(const std::vector<uint8_t>& data, const uint8_t key[32],
                  const std::string& output_path) {
    size_t min_sz = crypto_pwhash_SALTBYTES + 2 + crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES;
    if (!sodium_ready || data.size() < min_sz) return false;

    uint16_t nl;
    memcpy(&nl, data.data() + crypto_pwhash_SALTBYTES, 2);
    size_t hdr = crypto_pwhash_SALTBYTES + 2 + nl;
    if (data.size() < hdr + crypto_secretbox_NONCEBYTES + crypto_secretbox_MACBYTES) return false;

    const uint8_t* nonce  = data.data() + hdr;
    const uint8_t* cipher = nonce + crypto_secretbox_NONCEBYTES;
    size_t clen = data.size() - hdr;

    std::vector<uint8_t> plain(clen - crypto_secretbox_MACBYTES);
    if (crypto_secretbox_open_easy(plain.data(), cipher, clen, nonce, key) != 0)
        return false;

    std::string out_path = output_path.empty()
        ? std::string(data.begin() + crypto_pwhash_SALTBYTES + 2,
                      data.begin() + crypto_pwhash_SALTBYTES + 2 + nl)
        : output_path;

    std::ofstream f(out_path, std::ios::binary);
    if (!f) return false;
    f.write(reinterpret_cast<char*>(plain.data()), plain.size());
    return true;
}

std::string file_get_original_name(const std::vector<uint8_t>& data) {
    if (data.size() < crypto_pwhash_SALTBYTES + 2) return "unknown";
    uint16_t nl;
    memcpy(&nl, data.data() + crypto_pwhash_SALTBYTES, 2);
    if (data.size() < crypto_pwhash_SALTBYTES + 2 + nl) return "unknown";
    return std::string(data.begin() + crypto_pwhash_SALTBYTES + 2,
                       data.begin() + crypto_pwhash_SALTBYTES + 2 + nl);
}
