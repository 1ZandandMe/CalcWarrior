// crypto_utils.h — libsodium 加密工具封装
// 提供密钥派生、消息加解密、文件加解密
#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <string>
#include <vector>
#include <cstdint>

// ========== 密钥派生 ==========

// 从密码派生 32 字节加密密钥（Argon2id）
// password: 用户输入的密码
// key_out: 输出 32 字节密钥（crypto_secretbox_KEYBYTES）
// 返回 true 成功
bool derive_key(const std::string& password, uint8_t key_out[32]);

// ========== 消息加解密 ==========

// 加密消息（XSalsa20-Poly1305，带随机 nonce）
// plain: 明文（二进制）
// key: 32 字节密钥
// 返回: nonce(24字节) + ciphertext（含 MAC），可直接发送
// 失败返回空 vector
std::vector<uint8_t> msg_encrypt(const std::vector<uint8_t>& plain, const uint8_t key[32]);

// 解密消息
// packet: nonce + ciphertext（msg_encrypt 的输出）
// key: 32 字节密钥
// 返回明文，失败（MAC 不匹配 = 密码错误/数据损坏）返回空 vector
std::vector<uint8_t> msg_decrypt(const std::vector<uint8_t>& packet, const uint8_t key[32]);

// 字符串便捷版
std::vector<uint8_t> msg_encrypt(const std::string& plain, const uint8_t key[32]);
std::string msg_decrypt_to_string(const std::vector<uint8_t>& packet, const uint8_t key[32]);

// ========== 文件加解密 ==========

// 加密文件（一次性读入内存，适合 < 100MB 的文件）
// file_path: 文件路径
// key: 32 字节密钥
// 返回: salt(16) + 文件名长度(2) + 文件名 + nonce(24) + ciphertext
std::vector<uint8_t> file_encrypt(const std::string& file_path, const uint8_t key[32]);

// 解密文件到指定路径
// data: file_encrypt 的输出
// key: 32 字节密钥
// output_path: 输出路径（为空则使用原始文件名保存到当前目录）
// 返回 true 成功
bool file_decrypt(const std::vector<uint8_t>& data, const uint8_t key[32],
                  const std::string& output_path);

// 从加密数据中提取原始文件名
std::string file_get_original_name(const std::vector<uint8_t>& data);

#endif
