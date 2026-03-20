# 思维启发示例4：字典的创意应用
# 展示字典在数据处理中的多种用法

# 1. 基础字典操作
student = {
    "name": "张三",
    "age": 20,
    "courses": ["数学", "物理", "编程"],
    "scores": {"数学": 95, "物理": 88, "编程": 92}
}

print("学生信息:")
for key, value in student.items():
    print(f"  {key}: {value}")

# 2. 字典推导式
numbers = [1, 2, 3, 4, 5]
squares = {x: x**2 for x in numbers}
print(f"\n数字平方字典: {squares}")

# 3. 字典合并
info1 = {"name": "李四", "age": 22}
info2 = {"city": "北京", "major": "计算机"}
merged = {**info1, **info2}
print(f"\n合并后的信息: {merged}")

# 4. 默认值处理
from collections import defaultdict

# 统计单词频率
text = "apple banana apple orange banana apple"
words = text.split()
word_count = defaultdict(int)

for word in words:
    word_count[word] += 1

print(f"\n单词频率统计:")
for word, count in word_count.items():
    print(f"  '{word}': {count}次")

# 5. 字典作为简易数据库
inventory = {
    "apple": {"price": 1.2, "quantity": 50},
    "banana": {"price": 0.8, "quantity": 30},
    "orange": {"price": 1.5, "quantity": 20}
}

print(f"\n库存总价值计算:")
total_value = 0
for item, details in inventory.items():
    value = details["price"] * details["quantity"]
    total_value += value
    print(f"  {item}: ${value:.2f}")

print(f"库存总价值: ${total_value:.2f}")

# 启发：字典不只是键值对存储，还能用于统计、配置管理、简易数据库等