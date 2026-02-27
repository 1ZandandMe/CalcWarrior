# 指定 CMake 的最低版本要求（你的 CMake 版本要高于这个）
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(CalcWarrior)

# 设置 C++ 标准为 C++11（和你之前代码一致）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件，告诉 CMake 要用哪些源文件来生成 exe
add_executable(CalcWarrior 
    code/example.cpp
    code/shi.cpp
    code/sin.cpp
    code/ss.cpp
)