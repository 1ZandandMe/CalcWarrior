#include <pybind11/pybind11.h>  // 包含pybind11头文件
#include <iostream> 
// 定义一个简单的加法函数

int add(int i, int j) {

&#x20;   return i + j;  // 函数体：返回两个数的和

}

// 这是一个特殊的宏，用于创建Python模块

// 第一个参数是模块名，第二个参数是模块对象

PYBIND11\_MODULE(example, m) {

&#x20;   // 将C++函数add绑定到Python，取名为"add"

&#x20;   // 第三个参数是函数描述

&#x20;   m.def("add", \&add, "A function that adds two numbers.");
吗 
}