// #include <iostream>
// #include <string>
// using namespace std;

// string multiplyByTwo(string num) {
//     int carry = 0;
//     for (int i = num.size() - 1; i >= 0; i--) {
//         int digit = num[i] - '0';
//         int result = digit * 2 + carry;
//         num[i] = (result % 10) + '0';
//         carry = result / 10;
//     }
//     if (carry) num = to_string(carry) + num;
//     return num;
// }

// int main() {
//     string num = "1";
//     for (int i = 0; i < 1000; i++) {
//         num = multiplyByTwo(num);
//     }
//     cout << "2^1000 = " << num << endl;
//     cout << "位数：" << num.length() << endl;
//     return 0;
// }
// std::vector<int> vec(10000000);
// for (int i = 0; i < 10000000; ++i) {
//     vec[i] = i;
// }
// int fib(int n) {
//     return n < 2 ? n : fib(n-1) + fib(n-2);
// }
// // 编译优化后快很多

#include <iostream>
#include <chrono>

int main() {
    system("chcp 65001");
    auto start = std::chrono::high_resolution_clock::now();
    long long total = 0;
    for (int i = 0; i < 100000000; ++i) {
        total += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "C++ 耗时: " << elapsed.count() << "秒" << std::endl;
    return 0;
}