# 思维启发示例3：列表的多种遍历方式
# 展示不同遍历方法的应用场景

data = ["apple", "banana", "cherry", "date", "elderberry"]

# 1. 基础遍历
print("方法1: 直接遍历元素")
for fruit in data:
    print(f"  {fruit}")

# 2. 带索引遍历
print("\n方法2: 带索引遍历")
for i in range(len(data)):
    print(f"  索引{i}: {data[i]}")

# 3. 使用enumerate
print("\n方法3: 使用enumerate")
for index, fruit in enumerate(data):
    print(f"  位置{index}: {fruit}")

# 4. 反向遍历
print("\n方法4: 反向遍历")
for fruit in reversed(data):
    print(f"  {fruit}")

# 5. 同时遍历多个列表
prices = [1.2, 0.8, 2.5, 1.0, 3.0]
print("\n方法5: 同时遍历水果和价格")
for fruit, price in zip(data, prices):
    print(f"  {fruit}: ${price:.2f}")

# 6. 带条件的遍历
print("\n方法6: 只遍历长度大于5的水果")
long_fruits = [f for f in data if len(f) > 5]
for fruit in long_fruits:
    print(f"  {fruit}")

# 7. 使用while循环
print("\n方法7: 使用while循环")
i = 0
while i < len(data):
    print(f"  {data[i]}")
    i += 1

# 启发：不同的遍历方法适用于不同场景，选择合适的遍历方式能让代码更清晰高效