cmake_minimum_required(VERSION 3.15)
project(CalcWarrior CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# ========== 可执行程序 ==========
add_executable(calc_warrior code/main.cpp)   # 使用新建的 app.cpp


# ========== Python 扩展模块（可选，不影响可执行程序） ==========
option(BUILD_PYTHON_MODULE "Build Python extension module (pybind11)" ON)

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