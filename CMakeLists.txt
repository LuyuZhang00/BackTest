cmake_minimum_required(VERSION 3.10)  # 指定CMake的最小版本要求

project(BackTestDemo)  # 定义项目名称

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)
include_directories(include/utils/)

# 添加子目录
add_subdirectory(src)
add_subdirectory(test)

# 添加可执行文件
add_executable(BackTestDemo main.cpp)

# 链接库
target_link_libraries(BackTestDemo BackTestLib)