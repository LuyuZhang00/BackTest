#!/bin/bash

# 定义项目的根目录和构建目录
PROJECT_ROOT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="${PROJECT_ROOT_DIR}/build"

# 检查构建目录是否存在，如果存在则删除
if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# 创建构建目录
echo "====== Creating new build directory... ======"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# 运行 CMake 来配置项目
echo "====== Configuring project with CMake... ======"
cmake .. || { echo "CMake configuration failed"; exit 1; }

# 编译项目
echo "====== Building project... ======"
make  || { echo "Compilation failed"; exit 1; }

echo "====== Running DataLoaderTest... ======"
cd "test" || exit
./DataLoaderTest || { echo "Execution failed";}
./PortfolioManagerTest || { echo "Execution failed"; }
cd ..

# 运行编译好的程序
echo "====== Running BackTestDemo... ======"
./BackTestDemo || { echo "Execution failed"; exit 1; }


# 回到初始目录
cd "$PROJECT_ROOT_DIR" || exit
