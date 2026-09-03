#include <iostream>
#include <string>
#include <windows.h>  // system()

// ============================================================
// C++ 的类 —— 和 Python 核心区别
// ============================================================
// Python：类是运行时对象，__dict__ 可以随时增删属性
// C++：类是编译时蓝图，编译完属性就定死了，不能动态加
// Python：self 显式写在方法参数里
// C++：this 是隐式的，不用写，但存在

class Student {
    // --------------------------------------------------------
    // private：只有类自己的方法能访问
    // Python 没有真正的 private，全靠约定（_前缀）
    // --------------------------------------------------------
private:
    std::string name_;    // 成员变量 —— 相当于 Python 实例属性
    int grade_;      // 约定：成员变量末尾加 _ 以示区分

    // --------------------------------------------------------
    // public：外部可以访问
    // --------------------------------------------------------
public:
    // 静态成员变量 —— 最接近 Python 的"类属性"
    // 所有实例共享同一份
    // 注意：static 成员必须在类外面定义（见文件末尾）
    static std::string school;

    // 构造函数 —— 相当于 Python 的 __init__
    // 类名就是构造函数名，没有返回值
    Student(std::string name, int grade) {
        name_ = name;
        grade_ = grade;
    }

    // 方法 —— 不需要写 self/this 参数，编译器自动给
    void introduce() {
        std::cout << "我叫" << name_ << "，" << grade_ << "年级，来自" << school << std::endl;
    }

    void upgrade() {
        grade_++;
    }

    // 查看内部状态 —— C++ 没有 __dict__，只能自己写方法
    void show_state() {
        std::cout << "  name_ = " << name_ << std::endl;
        std::cout << "  grade_ = " << grade_ << std::endl;
    }
};

// ============================================================
// 静态成员变量必须在类外面定义
// 这一步 Python 不需要，因为在 Python 里 class 语句本身就是执行
// ============================================================
std::string Student::school = "榆林职高";

// ============================================================
int main() {
    std::system("chcp 65001");  // Windows 下用 UTF-8 编码输出中文
    // 造实例 —— 和 Python 的 s1 = Student("张三", 1) 一样
    Student s1("张三", 1);
    Student s2("李四", 2);

    // C++ 没有 __dict__，只能手动看状态
    std::cout << "=== s1 状态 ===" << std::endl;
    s1.show_state();
    std::cout << "=== s2 状态 ===" << std::endl;
    s2.show_state();

    // 方法调用
    std::cout << "\n=== 方法调用 ===" << std::endl;
    s1.introduce();
    s2.introduce();

    // 改实例自己的数据 —— 只影响 s1
    std::cout << "\n=== s1 升级 ===" << std::endl;
    s1.upgrade();
    std::cout << "s1 升级后：" << std::endl;
    s1.show_state();
    std::cout << "s2 不变：" << std::endl;
    s2.show_state();

    // 改静态成员 —— 和 Python 的 Student.school = "xxx" 一样
    std::cout << "\n=== 改学校 ===" << std::endl;
    std::cout << "改之前：s1.school = " << s1.school
              << " | s2.school = " << s2.school << std::endl;
    Student::school = "实验中学";
    std::cout << "改之后：s1.school = " << s1.school
              << " | s2.school = " << s2.school << std::endl;

    return 0;
}
