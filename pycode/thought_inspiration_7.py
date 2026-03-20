# 思维启发示例7：面向对象编程的实用模式
# 展示OOP在实际项目中的应用

class Student:
    """学生类 - 展示基本的OOP概念"""
    
    # 类属性（所有实例共享）
    school = "清华大学"
    
    def __init__(self, name, age, student_id):
        # 实例属性
        self.name = name
        self.age = age
        self.student_id = student_id
        self.courses = []  # 选修课程列表
        self.scores = {}   # 课程成绩字典
    
    def enroll_course(self, course_name):
        """选修课程"""
        if course_name not in self.courses:
            self.courses.append(course_name)
            print(f"{self.name} 选修了 {course_name}")
            return True
        return False
    
    def record_score(self, course_name, score):
        """记录成绩"""
        if course_name in self.courses:
            self.scores[course_name] = score
            print(f"{self.name} 的 {course_name} 成绩: {score}")
            return True
        print(f"错误: {self.name} 未选修 {course_name}")
        return False
    
    def calculate_average(self):
        """计算平均分"""
        if not self.scores:
            return 0
        return sum(self.scores.values()) / len(self.scores)
    
    def __str__(self):
        """字符串表示"""
        avg_score = self.calculate_average()
        return f"学生: {self.name} (ID: {self.student_id}), 平均分: {avg_score:.1f}"
    
    @classmethod
    def change_school(cls, new_school):
        """类方法 - 修改学校名称"""
        cls.school = new_school
        print(f"学校已改为: {new_school}")
    
    @staticmethod
    def is_valid_score(score):
        """静态方法 - 验证成绩是否有效"""
        return 0 <= score <= 100

class GraduateStudent(Student):
    """研究生类 - 继承自Student"""
    
    def __init__(self, name, age, student_id, research_topic):
        # 调用父类的初始化方法
        super().__init__(name, age, student_id)
        # 研究生特有属性
        self.research_topic = research_topic
        self.papers = []
    
    def publish_paper(self, paper_title):
        """发表论文"""
        self.papers.append(paper_title)
        print(f"{self.name} 发表了论文: {paper_title}")
    
    def __str__(self):
        """重写字符串表示"""
        base_info = super().__str__()
        return f"{base_info}, 研究方向: {self.research_topic}"

# 使用示例
print("=== 面向对象编程示例 ===")

# 创建本科生实例
student1 = Student("张三", 20, "2023001")
student1.enroll_course("Python编程")
student1.enroll_course("数据结构")
student1.record_score("Python编程", 95)
student1.record_score("数据结构", 88)

print(student1)
print(f"{student1.name} 的课程: {student1.courses}")
print(f"{student1.name} 的成绩: {student1.scores}")

# 创建研究生实例
grad_student = GraduateStudent("李四", 25, "G2023001", "人工智能")
grad_student.enroll_course("机器学习")
grad_student.record_score("机器学习", 92)
grad_student.publish_paper("深度学习在图像识别中的应用")

print(f"\n{grad_student}")
print(f"{grad_student.name} 的论文: {grad_student.papers}")

# 使用类方法
print(f"\n当前学校: {Student.school}")
Student.change_school("北京大学")
print(f"修改后学校: {Student.school}")

# 使用静态方法
test_scores = [95, 105, -5, 80]
print(f"\n成绩验证:")
for score in test_scores:
    valid = Student.is_valid_score(score)
    print(f"  成绩 {score}: {'有效' if valid else '无效'}")

# 启发：面向对象编程让代码更有组织性，继承和多态提高了代码的复用性