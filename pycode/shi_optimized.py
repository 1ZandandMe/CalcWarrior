# 列表count()方法示例 - 优化版
# 基于原shi.py文件，按照Python参考文档教学风格改进

## 示例说明
# 本示例演示如何使用列表的count()方法统计元素出现次数
# 原代码：a = ["kal","akl ","s","shis","kal"]

# 1. 创建测试列表
test_list = ["kal", "akl", "s", "shis", "kal"]
print("测试列表:", test_list)
print("列表长度:", len(test_list))

# 2. 使用count()方法统计特定元素
# 语法：list.count(obj) 返回元素obj在列表中出现的次数
kal_count = test_list.count("kal")
print(f"\n'kal'在列表中出现了{kal_count}次")

# 3. 统计所有元素的出现次数（优化版）
# 原代码的问题：对每个元素都调用count()，效率较低
# 优化方案：先获取唯一元素，再统计

print("\n=== 方法1：直接遍历统计（原方法）===")
for item in test_list:
    count = test_list.count(item)
    print(f"元素 '{item}' 出现了 {count} 次")

print("\n=== 方法2：使用集合去重后统计（优化方法）===")
unique_items = set(test_list)  # 使用集合去除重复元素
for item in unique_items:
    count = test_list.count(item)
    print(f"元素 '{item}' 出现了 {count} 次")

print("\n=== 方法3：使用字典统计（更高效）===")
item_count = {}
for item in test_list:
    if item in item_count:
        item_count[item] += 1
    else:
        item_count[item] = 1

for item, count in item_count.items():
    print(f"元素 '{item}' 出现了 {count} 次")

# 4. 扩展示例：处理边缘情况
print("\n=== 扩展示例：边缘情况处理 ===")

# 4.1 统计不存在的元素
non_existent = test_list.count("not_exist")
print(f"统计不存在的元素 'not_exist': {non_existent}次")

# 4.2 空列表统计
empty_list = []
print(f"空列表统计 'kal': {empty_list.count('kal')}次")

# 4.3 包含不同类型元素的列表
mixed_list = ["kal", 123, "kal", True, 123, "kal"]
print(f"\n混合类型列表: {mixed_list}")
print(f"字符串 'kal' 出现次数: {mixed_list.count('kal')}")
print(f"数字 123 出现次数: {mixed_list.count(123)}")
print(f"布尔值 True 出现次数: {mixed_list.count(True)}")

# 5. 性能比较
print("\n=== 性能比较 ===")
import time

# 创建大型测试列表
large_list = ["kal"] * 1000 + ["akl"] * 500 + ["s"] * 200 + ["shis"] * 100

# 方法1：原方法（效率较低）
start_time = time.time()
for item in large_list:
    large_list.count(item)
end_time = time.time()
print(f"原方法耗时: {end_time - start_time:.4f}秒")

# 方法2：优化方法
start_time = time.time()
unique_items = set(large_list)
for item in unique_items:
    large_list.count(item)
end_time = time.time()
print(f"优化方法耗时: {end_time - start_time:.4f}秒")

# 6. 实际应用：单词频率统计
print("\n=== 实际应用：文本分析 ===")
text = "kal akl s shis kal kal akl s"
words = text.split()
print(f"文本: {text}")
print(f"单词列表: {words}")

print("\n单词频率统计:")
word_freq = {}
for word in words:
    word_freq[word] = word_freq.get(word, 0) + 1

for word, freq in word_freq.items():
    print(f"'{word}': {freq}次 (使用count验证: {words.count(word)}次)")

# 7. 总结
print("\n" + "="*50)
print("总结：")
print("1. count()方法是列表的内置方法，用于统计元素出现次数")
print("2. 语法：list.count(obj)")
print("3. 如果元素不存在，返回0")
print("4. 对于大型列表，建议先获取唯一元素再统计以提高效率")
print("5. 实际应用中，字典统计通常更高效")
print("="*50)