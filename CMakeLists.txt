cmake_minimum_required(VERSION 3.15)
project(CalcWarrior CXX)

# ========== C++ 标准配置 ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========== 生成 compile_commands.json ==========
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== 输出目录配置 ==========
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ========== 编译选项配置 ==========
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 根据构建类型设置优化标志
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC/Clang 编译器
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0 -Wall -Wextra)
    else()
        add_compile_options(-O3 -DNDEBUG -Wall -Wextra)
    endif()
elseif(MSVC)
    # VSCode + MSVC 专用，自动区分Debug/Release，无冲突
    # 使用 target_compile_options 为目标添加编译选项，避免把生成器表达式传给 cl
    #（在文件级别的 add_compile_options 中使用生成器表达式会导致未展开的符号被传递给 cl）
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")


# ========== 可执行程序 ==========
add_executable(calc_warrior code/main.cpp)

# 设置目标属性
set_target_properties(calc_warrior PROPERTIES
    VERSION 1.0
    SOVERSION 1
)

# 为 MSVC 设置按配置的编译选项
if(MSVC)
    target_compile_options(calc_warrior PRIVATE
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/W4>
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/W4>
        $<$<CONFIG:Release>:/DNDEBUG>
    )
endif()
# 添加编译优化标志
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(calc_warrior PRIVATE
        $<$<CONFIG:Debug>:-g;-O0;-Wall;-Wextra;-pedantic>
        $<$<CONFIG:Release>:-O3;-march=native>
    )
endif()


# ========== Python 扩展模块（可选，不影响可执行程序） ==========
option(BUILD_PYTHON_MODULE "Build Python extension module (pybind11)" OFF)

if(BUILD_PYTHON_MODULE)
    find_package(Python COMPONENTS Interpreter Development.Module QUIET)
    find_package(pybind11 CONFIG QUIET)

    if(Python_FOUND AND pybind11_FOUND)
        pybind11_add_module(calcwarrior_py MODULE code/calcwarrior_py.cpp)
        set_target_properties(calcwarrior_py PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
        )
    else()
        message(WARNING "Python module build skipped: Python_FOUND=${Python_FOUND}, pybind11_FOUND=${pybind11_FOUND}. You can still build the executable.")
    endif()
endif()