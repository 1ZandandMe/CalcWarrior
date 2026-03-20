# Python列表操作示例 - 按照Python参考文档教学风格
# 本文件演示列表的基本操作、常用方法和实际应用

## 一、列表基础操作

### 1.1 列表创建与访问
# 列表用[]标识，是Python最通用的复合数据类型
list1 = ["kal", "akl", "s", "shis", "kal"]
print("完整列表:", list1)          # 输出完整列表
print("第一个元素:", list1[0])      # 输出列表第一个元素
print("第二个至第四个元素:", list1[1:4])  # 输出列表第二个至第四个元素
print("从第三个开始的所有元素:", list1[2:])  # 输出从第三个元素开始的所有元素

### 1.2 列表重复与拼接
tiny_list = ["test", "demo"]
print("列表重复:", tiny_list * 2)  # 输出列表两次
print("列表拼接:", list1 + tiny_list)  # 输出组合后的列表

## 二、列表常用方法

### 2.1 count()方法 - 统计元素出现次数
# list.count(obj)方法返回元素在列表中出现的次数
count_kal = list1.count("kal")
print(f"'kal'在列表中出现了{count_kal}次")

# 统计所有元素的出现次数
print("\n统计所有元素的出现次数:")
for item in list1:
    print(f"'{item}'出现了{list1.count(item)}次")

### 2.2 append()方法 - 添加元素
# list.append(obj)在列表末尾添加对象
list1.append("new_item")
print("\n添加元素后的列表:", list1)

### 2.3 index()方法 - 查找元素索引
# list.index(obj)返回元素的第一个匹配项的索引
try:
    kal_index = list1.index("kal")
    print(f"'kal'的第一个索引位置: {kal_index}")
except ValueError:
    print("元素不存在于列表中")

### 2.4 remove()方法 - 移除元素
# list.remove(obj)移除元素的第一个匹配项
list1.remove("akl")
print("移除'akl'后的列表:", list1)

### 2.5 extend()方法 - 扩展列表
# list.extend(seq)追加另一个序列的所有元素
extension = ["x", "y", "z"]
list1.extend(extension)
print("扩展后的列表:", list1)

## 三、列表遍历与操作

### 3.1 使用for循环遍历列表
print("\n使用for循环遍历列表:")
for i in range(len(list1)):
    print(f"索引{i}: {list1[i]}")

### 3.2 使用enumerate()获取索引和值
print("\n使用enumerate()遍历:")
for index, value in enumerate(list1):
    print(f"索引{index}: 值'{value}'")

### 3.3 列表推导式
# 创建新列表，包含原列表中长度大于1的字符串
long_items = [item for item in list1 if isinstance(item, str) and len(item) > 1]
print("\n长度大于1的字符串:", long_items)

## 四、实际应用示例

### 4.1 统计单词频率
words = ["apple", "banana", "apple", "orange", "banana", "apple"]
word_count = {}

for word in words:
    if word in word_count:
        word_count[word] += 1
    else:
        word_count[word] = 1

print("\n单词频率统计:")
for word, count in word_count.items():
    print(f"{word}: {count}次")

### 4.2 使用列表方法统计频率（更简洁的方式）
print("\n使用列表count()方法统计频率:")
unique_words = list(set(words))  # 去重
for word in unique_words:
    print(f"{word}: {words.count(word)}次")

### 4.3 列表排序
numbers = [3, 1, 4, 1, 5, 9, 2, 6, 5]
numbers.sort()
print("\n排序后的数字列表:", numbers)

# 降序排序
numbers.sort(reverse=True)
print("降序排序:", numbers)

## 五、与元组对比

### 5.1 列表与元组的区别
# 列表是可变的
my_list = [1, 2, 3]
my_list[0] = 100  # 合法操作
print(f"\n修改后的列表: {my_list}")

# 元组是不可变的
my_tuple = (1, 2, 3)
# my_tuple[0] = 100  # 这行代码会报错：TypeError
print(f"元组保持不变: {my_tuple}")

## 六、总结

"""
列表是Python中最常用的数据结构之一，具有以下特点：
1. 可变性：可以修改、添加、删除元素
2. 有序性：元素按照插入顺序存储
3. 可重复：允许包含重复元素
4. 支持多种数据类型：可以包含不同类型的元素

常用方法总结：
- count(): 统计元素出现次数
- append(): 在末尾添加元素
- extend(): 扩展列表
- index(): 查找元素索引
- remove(): 移除元素
- sort(): 排序列表
"""

print("\n" + "="*50)
print("示例代码执行完成！")
print("="*50)