// 猜数字 —— 一个完整的 C++ 小程序
// 编译：g++ guess_number.cpp -o guess_number.exe
// 运行：./guess_number.exe

#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time() 
#include <fstream>   // ofstream
#include <filesystem> // C++17 文件系统库


void shijian(int time_in_seconds[]) {
    time_t now = time(0);
    tm* t = localtime(&now);
    time_in_seconds[0] = t->tm_year + 1900;
    time_in_seconds[1] = t->tm_mon + 1;
    time_in_seconds[2] = t->tm_mday;
    time_in_seconds[3] = t->tm_hour;
    time_in_seconds[4] = t->tm_min;
    time_in_seconds[5] = t->tm_sec;
    std::cout << "游戏运行时间: " << time_in_seconds[0] << "-" << time_in_seconds[1] << "-" << time_in_seconds[2] << " " << time_in_seconds[3] << ":" << time_in_seconds[4] << ":" << time_in_seconds[5] << std::endl;
}

void output_record(int time_in_seconds[], int select, int fenshu, int i, const std::string& filename) {
    std::ofstream record_file(filename, std::ios::app); // 以追加模式打开文件
    record_file << time_in_seconds[3] << ":" << time_in_seconds[4] << ":" << time_in_seconds[5]
                << " | 难度:" << select << " | 得分:" << fenshu << " | 猜了" << i << "次" << std::endl;
    record_file.close();

}

int main() {
    system("chcp 65001"); // 设置控制台为 UTF-8 编码
    // 1. 初始化随机种子
    srand(time(0));

    int time_in_seconds[6];
    shijian(time_in_seconds);

    std::string filename = "records/"
      + std::to_string(time_in_seconds[0]) + "-"
      + std::to_string(time_in_seconds[1]) + "-"
      + std::to_string(time_in_seconds[2]) + ".txt"; // 以日期命名文件
    
    std::filesystem::create_directory("records");

    int select = 0;
    std::cout << "请选择难度级别(1-简单,2-中等,3-困难):";
    std::cin >> select;
    if (select == 1) {
        select = 100; // 默认范围是 1 到 100
    }else if (select == 2) {
        select = 500; // 中等范围是 1 到 500
    }else if (select == 3) {
        select = 1000; // 困难范围是 1 到 1000
    }else {
        std::cout << "无效的选择,默认使用简单难度1-100)。" << std::endl;
        select = 100; // 默认范围是 1 到 100
    }


    int fenshu = 100; 
    int koufen = 3; // 每次猜错扣分数

    // 2. 生成 1 到 select 之间的随机数

    int target = rand() %  select + 1; // 生成 1 到 100 之间的随机数
    int guess = 0; // 用户的猜测

    std::cout << "我想了一个 1 到 " << select << " 之间的数，你来猜。" << std::endl;

    int i = 0; // 猜测次数
    int dijiju = 0; 
    // 3. 循环：让用户反复猜，直到猜对
    while (true) {
        std::cout << "你猜多少？ ";
        std::cin >> guess;
        i++; // 猜测次数加 1
        // 4. 判断
        if (guess > target) {
            std::cout << "大了" << std::endl;
            fenshu -= koufen; // 猜错一次扣分
            if (fenshu <= 0) {
                if (dijiju >= 3) {
                    std::cout << "你已经失败了三次了，游戏结束！" << std::endl;
                    output_record(time_in_seconds, select, fenshu, i, filename);
                    break;
                }
                std::cout << "你的得分已经扣完了 重新来" << std::endl;
                output_record(time_in_seconds, select, fenshu, i, filename);
                target = rand() % select + 1;
                fenshu = 100; // 重置分数
                std::cout << select << " 之间的数，你来猜。" << std::endl;
                dijiju++;
                continue;
            }
        } else if (guess < target) {
            std::cout << "小了" << std::endl;
            fenshu -= koufen; // 猜错一次扣分
            if (fenshu <= 0) {
                if (dijiju >= 3) {
                    std::cout << "你已经失败了三次了，游戏结束！" << std::endl;
                    break;
                }
                output_record(time_in_seconds, select, fenshu, i, filename);
                std::cout << "你的得分已经扣完了 重新来" << std::endl;
                target = rand() % select + 1;
                fenshu = 100; // 重置分数
                std::cout << "新一局！我想了一个 1 到 " << select << " 之间的数。" << std::endl;
                std::cout << select << " 之间的数，你来猜。" << std::endl;
                dijiju++;
                continue;
                
            }

        } else if (guess == target) {
            std::cout << "对了！就是 " << target << std::endl;
            std::cout << "你猜了 " << i << " 次。" << std::endl;
            std::cout << "你的得分是: " << fenshu << " 分。" << std::endl;
            output_record(time_in_seconds, select, fenshu, i, filename);
            std::cout << "你还要继续玩吗？(输入1继续,其他退出) ";
            int c = 0;
            std::cin >> c;
            if(c == 1){
                target = rand() % select + 1;
                i = 0;
                fenshu = 100;
                std::cout << "新一局！我想了一个 1 到 " << select << " 之间的数。" << std::endl;
                continue;
            }else {
                break;
            }
        }
    }
    std::cout << "你的最终得分是: " << fenshu << " 分。" << std::endl;
    return 0;
}
