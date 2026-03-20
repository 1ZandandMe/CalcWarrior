# 思维启发示例1：数据类型的灵活转换
# 展示Python中类型转换的巧妙用法

# 1. 字符串与数字的相互转换
num_str = "123"
num_int = int(num_str)      # 字符串转整数
num_float = float(num_str)  # 字符串转浮点数
back_to_str = str(num_int)  # 数字转字符串

print(f"原始字符串: '{num_str}'")
print(f"转为整数: {num_int}")
print(f"转为浮点数: {num_float}")
print(f"再转回字符串: '{back_to_str}'")

# 2. 列表与字符串的转换
text = "hello world"
chars = list(text)          # 字符串转字符列表
words = text.split()        # 按空格分割成单词列表
joined = " ".join(words)    # 列表转回字符串

print(f"\n原始文本: '{text}'")
print(f"字符列表: {chars}")
print(f"单词列表: {words}")
print(f"重新组合: '{joined}'")

# 3. 元组与列表的转换
my_list = [1, 2, 3, 4, 5]
my_tuple = tuple(my_list)   # 列表转元组
back_to_list = list(my_tuple)  # 元组转列表

print(f"\n原始列表: {my_list}")
print(f"转为元组: {my_tuple}")
print(f"转回列表: {back_to_list}")

# 启发：数据类型转换是处理数据的基础，理解转换规则能写出更灵活的代码