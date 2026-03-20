# Python列表全面教程
# 按照《整理后的Python参考文档》教学风格编写

## 一、列表基础

### 1.1 列表创建与标识
# 列表用[]标识，是Python最通用的复合数据类型
# 列表可以包含不同类型的数据项

# 创建列表
list1 = ["kal", "akl", "s", "shis", "kal"]  # 字符串列表
list2 = [1, 2, 3, 4, 5]                     # 整数列表
list3 = [1, "hello", 3.14, True]            # 混合类型列表
list4 = []                                   # 空列表


print("字符串列表:", list1)
print("整数列表:", list2)
print("混合类型列表:时间", list3)
print("空列表:", list4)

### 1.2 列表访问与截取x
# 列表索引从0开始，支持正向和反向索引
print("\n=== 列表访问 ===")
print("list1[0]:", list1[0])        # 第一个元素
print("list1[-1]:", list1[-1])      # 最后一个元素
print("list1[-2]:", list1[-2])      # 倒数第二个元素

# 列表截取：[头下标:尾下标]
print("\n=== 列表截取 ===")
print("list1[1:3]:", list1[1:3])    # 第二个到第三个元素
print("list1[:3]:", list1[:3])      # 从开始到第三个元素
print("list1[2:]:", list1[2:])      # 从第三个到末尾
print("list1[:]:", list1[:])        # 完整列表（浅拷贝）
print("list1[::2]:", list1[::2])    # 步长为2

### 1.3 列表操作
print("\n=== 列表操作 ===")
print("列表重复:", list1 * 2)
print("列表拼接:", list1 + ["new", "items"])

## 二、列表方法详解

### 2.1 count()方法 - 统计元素出现次数
# list.count(obj) 返回元素在列表中出现的次数
print("\n=== count()方法 ===")
print("list1:", list1)
print("'kal'出现次数:", list1.count("kal"))
print("'akl'出现次数:", list1.count("akl"))
print("'not_exist'出现次数:", list1.count("not_exist"))  # 返回0

# 实际应用：统计单词频率
text = "apple banana apple orange banana apple"
words = text.split()
print(f"\n文本: {text}")
print(f"单词列表: {words}")
print(f"'apple'出现次数: {words.count('apple')}")

### 2.2 append()方法 - 添加元素
# list.append(obj) 在列表末尾添加对象
print("\n=== append()方法 ===")
numbers = [1, 2, 3]
print("原始列表:", numbers)
numbers.append(4)
print("添加4后:", numbers)
numbers.append([5, 6])  # 添加列表作为单个元素
print("添加列表后:", numbers)

### 2.3 extend()方法 - 扩展列表
# list.extend(seq) 追加另一个序列的所有元素
print("\n=== extend()方法 ===")
numbers = [1, 2, 3]
numbers.extend([4, 5])
print("扩展后:", numbers)

### 2.4 insert()方法 - 插入元素
# list.insert(index, obj) 在指定位置插入元素
print("\n=== insert()方法 ===")
fruits = ["apple", "banana", "cherry"]
fruits.insert(1, "orange")
print("插入后:", fruits)

### 2.5 remove()方法 - 移除元素
# list.remove(obj) 移除元素的第一个匹配项
print("\n=== remove()方法 ===")
fruits = ["apple", "banana", "cherry", "banana"]
print("原始列表:", fruits)
fruits.remove("banana")
print("移除第一个'banana'后:", fruits)

### 2.6 pop()方法 - 弹出元素
# list.pop([index]) 移除指定位置的元素并返回该元素
print("\n=== pop()方法 ===")
fruits = ["apple", "banana", "cherry"]
popped = fruits.pop(1)
print(f"弹出索引1的元素: {popped}")
print("弹出后列表:", fruits)

### 2.7 index()方法 - 查找元素索引
# list.index(obj) 返回元素的第一个匹配项的索引
print("\n=== index()方法 ===")
fruits = ["apple", "banana", "cherry", "banana"]
print("'banana'的第一个索引:", fruits.index("banana"))

### 2.8 sort()方法 - 列表排序
# list.sort(key=None, reverse=False) 对原列表进行排序
print("\n=== sort()方法 ===")
numbers = [3, 1, 4, 1, 5, 9, 2]
numbers.sort()
print("升序排序:", numbers)
numbers.sort(reverse=True)
print("降序排序:", numbers)

### 2.9 reverse()方法 - 反转列表
# list.reverse() 反转列表中的元素
print("\n=== reverse()方法 ===")
numbers = [1, 2, 3, 4, 5]
numbers.reverse()
print("反转后:", numbers)

### 2.10 copy()方法 - 列表复制
# list.copy() 返回列表的浅拷贝
print("\n=== copy()方法 ===")
original = [1, 2, 3]
copied = original.copy()
copied.append(4)
print("原始列表:", original)
print("复制并修改后的列表:", copied)

## 三、列表遍历

### 3.1 使用for循环遍历
print("\n=== for循环遍历 ===")
fruits = ["apple", "banana", "cherry"]
print("直接遍历元素:")
for fruit in fruits:
    print(f"  {fruit}")

print("\n使用range()遍历索引:")
for i in range(len(fruits)):
    print(f"  索引{i}: {fruits[i]}")

### 3.2 使用enumerate()同时获取索引和值
print("\n=== enumerate()遍历 ===")
for index, fruit in enumerate(fruits):
    print(f"  索引{index}: {fruit}")

### 3.3 使用while循环遍历
print("\n=== while循环遍历 ===")
i = 0
while i < len(fruits):
    print(f"  索引{i}: {fruits[i]}")
    i += 1

## 四、列表推导式

### 4.1 基本列表推导式
print("\n=== 列表推导式 ===")
# 创建平方数列表
squares = [x**2 for x in range(1, 6)]
print("1-5的平方:", squares)

# 过滤偶数
evens = [x for x in range(10) if x % 2 == 0]
print("0-9的偶数:", evens)

### 4.2 复杂列表推导式
# 嵌套循环
pairs = [(x, y) for x in range(3) for y in range(3)]
print("坐标对:", pairs)

## 五、实际应用示例

### 5.1 学生成绩统计
print("\n=== 学生成绩统计 ===")
grades = [85, 92, 78, 90, 85, 92, 88, 85]

# 统计每个分数的出现次数
grade_count = {}
for grade in grades:
    grade_count[grade] = grade_count.get(grade, 0) + 1

print("成绩列表:", grades)
print("成绩分布:")
for grade, count in sorted(grade_count.items()):
    print(f"  {grade}分: {count}人")

# 使用count()验证
print("\n使用count()验证:")
for grade in set(grades):
    print(f"  {grade}分: {grades.count(grade)}人")

### 5.2 文本处理
print("\n=== 文本处理 ===")
sentence = "Python is powerful and Python is easy to learn"
words = sentence.split()

# 统计单词长度
word_lengths = [len(word) for word in words]
print("句子:", sentence)
print("单词长度列表:", word_lengths)
print("平均单词长度:", sum(word_lengths) / len(word_lengths))

### 5.3 数据过滤
print("\n=== 数据过滤 ===")
data = [23, 45, 12, 67, 89, 34, 56, 78]
threshold = 50

# 过滤大于阈值的数据
filtered_data = [x for x in data if x > threshold]
print("原始数据:", data)
print(f"大于{threshold}的数据:", filtered_data)

## 六、性能优化技巧

### 6.1 避免在循环中重复调用count()
print("\n=== 性能优化 ===")
large_list = ["item"] * 10000 + ["other"] * 5000

# 低效方法（重复遍历）
print("低效方法测试...")
import time
start = time.time()
for item in large_list:
    large_list.count(item)
end = time.time()
print(f"耗时: {end-start:.4f}秒")

# 高效方法（使用集合）
print("\n高效方法测试...")
start = time.time()
unique_items = set(large_list)
for item in unique_items:
    large_list.count(item)
end = time.time()
print(f"耗时: {end-start:.4f}秒")

### 6.2 使用适当的数据结构
# 对于频繁的查找操作，考虑使用集合或字典
print("\n=== 数据结构选择 ===")
# 如果需要快速判断元素是否存在，使用集合
my_set = set(["apple", "banana", "cherry"])
print("'apple'在集合中:", "apple" in my_set)  # O(1)时间复杂度

## 七、总结

print("\n" + "="*60)
print("Python列表核心知识点总结:")
print("="*60)
print("""
1. 列表特性：
   - 可变：可以修改、添加、删除元素
   - 有序：元素按照插入顺序存储
   - 可重复：允许包含相同元素
   - 支持索引：通过下标访问元素

2. 常用方法：
   - 统计：count(obj)
   - 添加：append(obj), extend(seq), insert(index, obj)
   - 删除：remove(obj), pop([index])
   - 查找：index(obj)
   - 排序：sort(), reverse()

3. 遍历方式：
   - for item in list:
   - for i in range(len(list)):
   - enumerate(list)

4. 高级特性：
   - 列表推导式：[expression for item in iterable]
   - 切片操作：[start:end:step]
   - 深浅拷贝：copy(), 列表切片[:]

5. 性能建议：
   - 避免在循环中重复调用count()
   - 大型列表考虑使用集合或字典
   - 使用适当的数据结构优化性能
""")
print("="*60)
print("教程结束，建议运行代码查看具体输出结果！")
print("="*60)