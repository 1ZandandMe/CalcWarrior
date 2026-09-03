#include <iostream>

class lr {
private:
    int count = 0;
public:
    void increment() {
        count++;
    }
    // int add() { return count; }   // [原] 名字叫 add 容易误会，其实它是"返回计数"
    int getCount() {                 // [改] 改成 getCount，语义清楚
        return count;
    }
    int printFive(int n) {
        // int n;                    // [原] 这行是 bug：跟参数 n 重名遮蔽参数 → 删掉才能编
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < 5; ++i) {
                increment();
            }
        }
        return getCount();           // [改] 原先是 return add();
    }
};



int main() {
    system("chcp 65001"); // 设置控制台编码，支持中文输出
    lr a;
    int n;
    std::cout << "你想要几个五：";
    std::cin >> n;
    int result = a.printFive(n);
    // 执行 n 次“五连加”，每次 for 循环增加 5
    std::cout << "总计数为：" << result << std::endl;

    return 0;
}