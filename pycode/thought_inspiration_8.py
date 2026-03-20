# 思维启发示例8：综合应用 - 简易学生管理系统
# 结合多个知识点解决实际问题

import json
import os
from datetime import datetime
from typing import List, Dict, Optional

class SimpleStudentSystem:
    """简易学生管理系统 - 综合应用示例"""
    
    def __init__(self, data_file="students.json"):
        self.data_file = data_file
        self.students = self.load_data()
    
    def load_data(self) -> Dict:
        """加载学生数据"""
        if os.path.exists(self.data_file):
            try:
                with open(self.data_file, 'r', encoding='utf-8') as f:
                    return json.load(f)
            except Exception as e:
                print(f"加载数据失败: {e}")
                return {}
        return {}
    
    def save_data(self):
        """保存学生数据"""
        try:
            with open(self.data_file, 'w', encoding='utf-8') as f:
                json.dump(self.students, f, ensure_ascii=False, indent=2)
            return True
        except Exception as e:
            print(f"保存数据失败: {e}")
            return False
    
    def add_student(self, student_id: str, name: str, age: int, major: str) -> bool:
        """添加学生"""
        if student_id in self.students:
            print(f"学生ID {student_id} 已存在")
            return False
        
        self.students[student_id] = {
            "name": name,
            "age": age,
            "major": major,
            "courses": {},
            "created_at": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        }
        self.save_data()
        print(f"成功添加学生: {name} (ID: {student_id})")
        return True
    
    def add_course_score(self, student_id: str, course: str, score: float) -> bool:
        """添加课程成绩"""
        if student_id not in self.students:
            print(f"学生ID {student_id} 不存在")
            return False
        
        if not (0 <= score <= 100):
            print(f"成绩 {score} 无效，应在0-100之间")
            return False
        
        self.students[student_id]["courses"][course] = score
        self.save_data()
        print(f"为 {self.students[student_id]['name']} 添加 {course} 成绩: {score}")
        return True
    
    def get_student_info(self, student_id: str) -> Optional[Dict]:
        """获取学生信息"""
        return self.students.get(student_id)
    
    def calculate_statistics(self):
        """计算统计信息"""
        if not self.students:
            print("没有学生数据")
            return
        
        total_students = len(self.students)
        majors = {}
        age_sum = 0
        
        for student_id, info in self.students.items():
            # 统计专业分布
            major = info["major"]
            majors[major] = majors.get(major, 0) + 1
            
            # 计算年龄总和
            age_sum += info["age"]
        
        print(f"\n=== 系统统计信息 ===")
        print(f"学生总数: {total_students}")
        print(f"平均年龄: {age_sum/total_students:.1f}")
        print(f"专业分布:")
        for major, count in majors.items():
            percentage = (count / total_students) * 100
            print(f"  {major}: {count}人 ({percentage:.1f}%)")
    
    def find_top_students(self, n: int = 3):
        """查找成绩最好的学生"""
        student_scores = []
        
        for student_id, info in self.students.items():
            courses = info.get("courses", {})
            if courses:
                avg_score = sum(courses.values()) / len(courses)
                student_scores.append((info["name"], avg_score, student_id))
        
        if not student_scores:
            print("没有成绩数据")
            return
        
        # 按平均分排序
        student_scores.sort(key=lambda x: x[1], reverse=True)
        
        print(f"\n=== 前{n}名学生 ===")
        for i, (name, avg_score, student_id) in enumerate(student_scores[:n], 1):
            print(f"{i}. {name} (ID: {student_id}): {avg_score:.1f}分")
    
    def search_students(self, keyword: str):
        """搜索学生"""
        results = []
        
        for student_id, info in self.students.items():
            # 在姓名和专业中搜索关键词
            if (keyword.lower() in info["name"].lower() or 
                keyword.lower() in info["major"].lower()):
                results.append((student_id, info))
        
        if not results:
            print(f"未找到包含 '{keyword}' 的学生")
            return
        
        print(f"\n=== 搜索 '{keyword}' 的结果 ===")
        for student_id, info in results:
            courses = info.get("courses", {})
            avg_score = sum(courses.values()) / len(courses) if courses else 0
            print(f"ID: {student_id}, 姓名: {info['name']}, "
                  f"专业: {info['major']}, 平均分: {avg_score:.1f}")
    
    def export_report(self, filename: str = "student_report.txt"):
        """导出学生报告"""
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                f.write("=== 学生管理系统报告 ===\n")
                f.write(f"生成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write(f"学生总数: {len(self.students)}\n\n")
                
                for student_id, info in self.students.items():
                    f.write(f"学生ID: {student_id}\n")
                    f.write(f"姓名: {info['name']}\n")
                    f.write(f"年龄: {info['age']}\n")
                    f.write(f"专业: {info['major']}\n")
                    
                    courses = info.get("courses", {})
                    if courses:
                        avg_score = sum(courses.values()) / len(courses)
                        f.write(f"平均分: {avg_score:.1f}\n")
                        f.write("课程成绩:\n")
                        for course, score in courses.items():
                            f.write(f"  {course}: {score}\n")
                    else:
                        f.write("暂无成绩\n")
                    
                    f.write("-" * 40 + "\n")
            
            print(f"报告已导出到: {filename}")
            return True
        except Exception as e:
            print(f"导出报告失败: {e}")
            return False

# 使用示例
def demo_student_system():
    """演示学生管理系统"""
    print("=== 简易学生管理系统演示 ===\n")
    
    # 创建系统实例
    system = SimpleStudentSystem()
    
    # 添加学生
    system.add_student("2023001", "张三", 20, "计算机科学")
    system.add_student("2023002", "李四", 21, "软件工程")
    system.add_student("2023003", "王五", 19, "计算机科学")
    system.add_student("2023004", "赵六", 22, "人工智能")
    
    # 添加课程成绩
    system.add_course_score("2023001", "Python编程", 95)
    system.add_course_score("2023001", "数据结构", 88)
    system.add_course_score("2023002", "Python编程", 92)
    system.add_course_score("2023002", "算法设计", 85)
    system.add_course_score("2023003", "Python编程", 78)
    system.add_course_score("2023004", "机器学习", 96)
    
    # 查看学生信息
    print("\n=== 查看学生信息 ===")
    student_info = system.get_student_info("2023001")
    if student_info:
        print(f"姓名: {student_info['name']}")
        print(f"年龄: {student_info['age']}")
        print(f"专业: {student_info['major']}")
        print(f"课程成绩: {student_info.get('courses', {})}")
    
    # 计算统计信息
    system.calculate_statistics()
    
    # 查找优秀学生
    system.find_top_students(3)
    
    # 搜索学生
    system.search_students("计算机")
    
    # 导出报告
    system.export_report()
    
    print("\n=== 演示完成 ===")

# 运行演示
if __name__ == "__main__":
    demo_student_system()

# 启发：综合应用多个知识点可以构建实用的系统，良好的代码组织让项目更易维护