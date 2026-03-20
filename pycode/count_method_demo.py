# Python列表count()方法深度解析
# 按照Python参考文档教学风格编写

## 一、count()方法基础

### 1.1 方法定义
# list.count(obj)方法返回元素obj在列表中出现的次数
# 语法：list.count(obj)
# 参数：obj - 要在列表中统计的对象
# 返回值：整数，表示obj在列表中出现的次数

### 1.2 基本用法示例
fruits = ["apple", "banana", "apple", "orange", "banana", "apple", "grape"]

# 统计单个元素的出现次数
apple_count = fruits.count("apple")
banana_count = fruits.count("banana")
orange_count = fruits.count("orange")
grape_count = fruits.count("grape")

print("水果列表:", fruits)
print(f"'apple'出现了{apple_count}次")
print(f"'banana'出现了{banana_count}次")
print(f"'orange'出现了{orange_count}次")
print(f"'grape'出现了{grape_count}次")

## 二、count()方法的高级应用

### 2.1 统计不同类型的数据
mixed_list = [1, 2.5, "hello", True, 1, "hello", 1, False, "hello"]
print("\n混合类型列表:", mixed_list)

print(f"数字1出现了{mixed_list.count(1)}次")
print(f"字符串'hello'出现了{mixed_list.count('hello')}次")
print(f"布尔值True出现了{mixed_list.count(True)}次")
print(f"布尔值False出现了{mixed_list.count(False)}次")

# 注意：在Python中，True和1、False和0有特殊关系
print(f"\n注意:True == 1 是 {True == 1}")
print(f"False == 0 是 {False == 0}")
print(f"但True is 1 是 {True is 1}")  # 不是同一个对象

### 2.2 统计不存在的元素
print("\n统计不存在的元素:")
print(f"'watermelon'出现了{fruits.count('watermelon')}次")  # 返回0

### 2.3 在嵌套列表中使用
nested_list = [[1, 2], [3, 4], [1, 2], [5, 6]]
target = [1, 2]
print(f"\n嵌套列表: {nested_list}")
print(f"子列表[1, 2]出现了{nested_list.count(target)}次")

## 三、实际应用场景

### 3.1 文本分析 - 统计单词频率
text = "the quick brown fox jumps over the lazy dog the dog is brown"
words = text.split()

print("\n文本分析:")
print(f"原始文本: {text}")
print(f"单词列表: {words}")

# 统计每个单词的出现次数
unique_words = list(set(words))
print("\n单词频率统计:")
for word in unique_words:
    count = words.count(word)
    print(f"'{word}': {count}次")

### 3.2 数据清洗 - 查找重复数据
data = [100, 200, 100, 300, 200, 400, 100, 500]
print(f"\n数据列表: {data}")

# 找出所有重复的数据项
duplicates = []
for item in data:
    if data.count(item) > 1 and item not in duplicates:
        duplicates.append(item)

print(f"重复的数据项: {duplicates}")
for item in duplicates:
    print(f"  {item} 出现了{data.count(item)}次")

### 3.3 投票统计
votes = ["Alice", "Bob", "Alice", "Charlie", "Bob", "Alice", "Bob", "Alice"]
candidates = list(set(votes))

print(f"\n投票结果: {votes}")
print("候选人得票统计:")
for candidate in sorted(candidates):
    vote_count = votes.count(candidate)
    print(f"  {candidate}: {vote_count}票")

## 四、性能考虑与替代方案

### 4.1 count()方法的性能
# count()方法的时间复杂度是O(n)，对于大型列表可能较慢
large_list = list(range(10000)) + [9999] * 10

print("\n性能测试:")
print("在包含10010个元素的列表中查找9999...")

import time
start_time = time.time()
count_9999 = large_list.count(9999)
end_time = time.time()

print(f"找到9999出现了{count_9999}次")
print(f"耗时: {end_time - start_time:.6f}秒")

### 4.2 使用collections.Counter提高性能
from collections import Counter

print("\n使用collections.Counter:")
counter = Counter(votes)
print("投票统计结果:")
for candidate, count in counter.items():
    print(f"  {candidate}: {count}票")

### 4.3 使用字典手动统计
print("\n使用字典手动统计:")
word_count = {}
for word in words:
    if word in word_count:
        word_count[word] += 1
    else:
        word_count[word] = 1

print("单词频率统计:")
for word, count in word_count.items():
    print(f"  '{word}': {count}次")

## 五、练习与测试

### 5.1 练习题
print("\n" + "="*50)
print("练习题:")
print("1. 创建一个包含重复数字的列表，使用count()找出出现次数最多的数字")
print("2. 统计一段英文文本中每个字母的出现频率")
print("3. 比较count()方法和Counter的性能差异")
print("="*50)

### 5.2 练习1示例
numbers = [1, 2, 3, 2, 1, 4, 2, 5, 2, 1]
unique_numbers = list(set(numbers))
max_count = 0
most_common = None

for num in unique_numbers:
    current_count = numbers.count(num)
    if current_count > max_count:
        max_count = current_count
        most_common = num

print(f"\n练习1答案:")
print(f"数字列表: {numbers}")
print(f"出现次数最多的数字是 {most_common}，出现了 {max_count} 次")

## 六、总结

"""
count()方法总结：

优点：
1. 语法简单，易于使用
2. 直接内置于列表对象中
3. 适用于快速统计小规模数据

缺点：
1. 时间复杂度O(n)，对于大型列表效率较低
2. 每次调用都会遍历整个列表

适用场景：
- 小型到中型列表
- 不需要频繁统计的场景
- 简单的重复检测

替代方案：
- collections.Counter：适用于频繁统计和大规模数据
- 字典手动统计：更灵活，可以自定义逻辑
"""

print("\n" + "="*50)
print("count()方法教学完成！")
print("="*50)