# 思维启发示例2：字符串的切片魔法
# 展示字符串切片的多种创意用法

text = "PythonProgrammingIsFun"

# 1. 基础切片
print(f"完整字符串: {text}")
print(f"前6个字符: {text[:6]}")      # Python
print(f"第7个开始: {text[6:]}")      # ProgrammingIsFun
print(f"每隔一个字符: {text[::2]}")   # Pto rgamn sFn
print(f"反转字符串: {text[::-1]}")    # nuFsIgnimmargorPnohtyP

# 2. 提取特定模式
# 提取所有大写字母
uppercase = ''.join([c for c in text if c.isupper()])
print(f"\n所有大写字母: {uppercase}")

# 提取单词（按大写字母分割）
import re
words = re.findall('[A-Z][a-z]*', text)
print(f"按大写分割的单词: {words}")

# 3. 创意切片应用
# 创建回文检查
def is_palindrome(s):
    return s == s[::-1]

test_words = ["radar", "python", "level", "hello"]
print(f"\n回文检查:")
for word in test_words:
    print(f"  '{word}': {is_palindrome(word)}")

# 4. 字符串编码转换
original = "你好世界"
utf8_bytes = original.encode('utf-8')
back_to_str = utf8_bytes.decode('utf-8')

print(f"\n编码转换示例:")
print(f"原始: {original}")
print(f"UTF-8字节: {utf8_bytes}")
print(f"解码后: {back_to_str}")

# 启发：字符串切片不只是提取子串，还能用于反转、模式匹配、编码处理等