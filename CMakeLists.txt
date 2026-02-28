# 适配你的4.1版本，最低兼容3.15，向下兼容无压力
cmake_minimum_required(VERSION 3.15)

# 你的项目名称，按要求设置为CALC_WARRIOR，指定为C++项目
project(CalcWarrior CXX)

# 设置C++标准，用主流稳定的C++17，兼容所有计算类代码、SMILES处理库
set(CMAKE_CXX_STANDARD 17)
# 强制要求编译器支持该C++标准，避免兼容问题
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 关闭编译器专属扩展，保证Windows/Linux/Mac跨平台兼容
set(CMAKE_CXX_EXTENSIONS OFF)

# 核心配置：添加可执行程序
# 格式：add_executable(生成的程序名  你的源码文件.cpp)
# 说明：
# 1. 生成的程序名设为calc_warrior，和项目名对应
# 2. 这里写你的cpp源码文件名，比如你叫main.cpp就写main.cpp，空文件也能正常配置
# 3. 后续加新的cpp文件，直接空格加在后面即可，比如 add_executable(calc_warrior main.cpp smile_utils.cpp)
add_executable(calc_warrior code/main.cpp)