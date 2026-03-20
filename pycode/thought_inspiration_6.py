# 思维启发示例6：文件操作与异常处理
# 展示实际项目中的文件处理模式

import os
import json

# 1. 基础文件读写
def read_file_safely(filename):
    """安全读取文件，包含异常处理"""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print(f"错误: 文件 '{filename}' 不存在")
        return None
    except PermissionError:
        print(f"错误: 没有权限读取文件 '{filename}'")
        return None
    except Exception as e:
        print(f"未知错误: {e}")
        return None

def write_file_safely(filename, content):
    """安全写入文件"""
    try:
        with open(filename, 'w', encoding='utf-8') as file:
            file.write(content)
        print(f"成功写入文件: {filename}")
        return True
    except Exception as e:
        print(f"写入文件失败: {e}")
        return False

# 2. JSON文件处理
def save_to_json(data, filename):
    """保存数据到JSON文件"""
    try:
        with open(filename, 'w', encoding='utf-8') as file:
            json.dump(data, file, ensure_ascii=False, indent=2)
        print(f"数据已保存到 {filename}")
        return True
    except Exception as e:
        print(f"保存JSON失败: {e}")
        return False

def load_from_json(filename):
    """从JSON文件加载数据"""
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            data = json.load(file)
        print(f"从 {filename} 加载数据成功")
        return data
    except FileNotFoundError:
        print(f"文件 {filename} 不存在")
        return {}
    except json.JSONDecodeError:
        print(f"文件 {filename} 不是有效的JSON格式")
        return {}
    except Exception as e:
        print(f"加载JSON失败: {e}")
        return {}

# 3. 文件系统操作
def list_files_in_directory(path="."):
    """列出目录中的文件"""
    try:
        files = os.listdir(path)
        print(f"\n目录 '{path}' 中的文件:")
        for file in files:
            filepath = os.path.join(path, file)
            if os.path.isfile(filepath):
                size = os.path.getsize(filepath)
                print(f"  文件: {file} ({size} 字节)")
            else:
                print(f"  目录: {file}/")
        return files
    except Exception as e:
        print(f"列出目录失败: {e}")
        return []

# 4. 实际应用示例
# 创建测试数据
test_data = {
    "students": [
        {"name": "张三", "age": 20, "score": 95},
        {"name": "李四", "age": 21, "score": 88},
        {"name": "王五", "age": 19, "score": 92}
    ],
    "course": "Python编程",
    "date": "2026-03-11"
}

# 测试函数
print("=== 文件操作示例 ===")

# 保存到JSON
save_to_json(test_data, "test_data.json")

# 从JSON加载
loaded_data = load_from_json("test_data.json")
if loaded_data:
    print(f"加载的数据: {json.dumps(loaded_data, ensure_ascii=False, indent=2)}")

# 列出当前目录文件
list_files_in_directory()

# 清理测试文件
if os.path.exists("test_data.json"):
    os.remove("test_data.json")
    print("\n已清理测试文件")

# 启发：良好的异常处理能让程序更健壮，文件操作是数据持久化的基础