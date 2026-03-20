# 思维启发示例5：函数与lambda表达式的灵活运用
# 展示函数式编程思想

# 1. 基础函数定义
def process_text(text, operation):
    """处理文本的通用函数"""
    return operation(text)

# 2. 定义不同的处理操作
def to_upper(s):
    return s.upper()

def reverse_text(s):
    return s[::-1]

def count_vowels(s):
    vowels = "aeiouAEIOU"
    return sum(1 for c in s if c in vowels)

# 3. 使用函数作为参数
text = "Hello World"
print(f"原始文本: {text}")
print(f"转为大写: {process_text(text, to_upper)}")
print(f"反转文本: {process_text(text, reverse_text)}")
print(f"元音数量: {process_text(text, count_vowels)}")

# 4. 使用lambda表达式
print(f"\n使用lambda表达式:")
print(f"转为小写: {process_text(text, lambda s: s.lower())}")
print(f"单词数量: {process_text(text, lambda s: len(s.split()))}")
print(f"去除空格: {process_text(text, lambda s: s.replace(' ', ''))}")

# 5. map、filter、reduce的应用
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# 使用map进行转换
squared = list(map(lambda x: x**2, numbers))
print(f"\n数字列表: {numbers}")
print(f"平方后: {squared}")

# 使用filter进行过滤
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(f"偶数: {even_numbers}")

# 使用reduce进行累积计算
from functools import reduce
product = reduce(lambda x, y: x * y, numbers)
print(f"所有数字的乘积: {product}")

# 6. 闭包的应用
def make_multiplier(n):
    """创建乘法器函数"""
    def multiplier(x):
        return x * n
    return multiplier

double = make_multiplier(2)
triple = make_multiplier(3)

print(f"\n闭包示例:")
print(f"double(5) = {double(5)}")
print(f"triple(5) = {triple(5)}")

# 启发：函数可以作为参数传递，lambda表达式让代码更简洁，函数式编程思想能提高代码的复用性