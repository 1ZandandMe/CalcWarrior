#include <iostream>
#include <chrono>

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        std::cout << i << std::endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto endl_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        std::cout << i << '\n';
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto nl_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "endl: " << endl_time.count() << " ms\n";
    std::cout << "'\\n': " << nl_time.count() << " ms\n";
}