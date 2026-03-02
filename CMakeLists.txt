cmake_minimum_required(VERSION 3.15)
project(CalcWarrior CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ========== 可执行程序 ==========
add_executable(calc_warrior code/main.cpp)   # 使用新建的 app.cpp