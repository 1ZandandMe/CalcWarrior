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

# ========== 默认构建类型 ==========
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

# ========== 自动收集所有 .cpp 源文件 ==========
file(GLOB_RECURSE ALL_CPP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/code/*.cpp"
)

if(NOT ALL_CPP_SOURCES)
    message(WARNING "No .cpp files found in ${CMAKE_CURRENT_SOURCE_DIR}/code/")
endif()

# ========== 为每个 .cpp 文件生成一个可执行目标 ==========
foreach(CPP_FILE ${ALL_CPP_SOURCES})
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${CPP_FILE})
    
    set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION 1.0
        SOVERSION 1
    )
    
    # 统一编译选项（基于编译器和构建类型）
    target_compile_options(${TARGET_NAME} PRIVATE
        # GNU / Clang 选项
        $<$<CXX_COMPILER_ID:GNU,Clang>:
            $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra -pedantic>
            $<$<CONFIG:Release>:-O3 -DNDEBUG -Wall -Wextra -march=native>
        >
        # MSVC 选项（包含 /utf-8 解决中文乱码）
        $<$<CXX_COMPILER_ID:MSVC>:
            $<$<CONFIG:Debug>:/Od /W4 /utf-8>
            $<$<CONFIG:Release>:/O2 /W4 /DNDEBUG /utf-8>
        >
    )
    
    # 如需添加头文件目录，取消注释并修改路径
    # target_include_directories(${TARGET_NAME} PRIVATE include)
    
    message(STATUS "Added executable target: ${TARGET_NAME} from ${CPP_FILE}")
endforeach()

# ========== Python 扩展模块（可选） ==========
option(BUILD_PYTHON_MODULE "Build Python extension module (pybind11)" OFF)

if(BUILD_PYTHON_MODULE)
    find_package(Python 3.8 COMPONENTS Interpreter Development.Module QUIET)
    find_package(pybind11 CONFIG QUIET)

    if(Python_FOUND AND pybind11_FOUND)
        pybind11_add_module(calcwarrior_py MODULE code/calcwarrior_py.cpp)
        set_target_properties(calcwarrior_py PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
        )
        message(STATUS "Python module will be built.")
    else()
        message(WARNING "Python module build skipped.")
    endif()
endif()