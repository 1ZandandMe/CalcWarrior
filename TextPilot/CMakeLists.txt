cmake_minimum_required(VERSION 3.15)
project(TextPilot VERSION 3.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TextPilot
    src/main.cpp
    src/config.cpp
    src/HistoryBuffer.cpp
    src/KeyboardSimulator.cpp
    src/TextInputService.cpp
    src/ClipboardManager.cpp
    src/DiscoveryService.cpp
)

target_include_directories(TextPilot PRIVATE include src)
target_link_libraries(TextPilot PRIVATE ws2_32 user32)

if(MSVC)
    target_compile_options(TextPilot PRIVATE /W4)
endif()
