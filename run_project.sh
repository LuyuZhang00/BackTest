#!/bin/bash

# 定义项目的根目录和构建目录
DATA_FILE="/home/zhangluyu/code/BackTest/data/stock_data.csv"
PROJECT_ROOT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="${PROJECT_ROOT_DIR}/build"
LOG_DIR="${PROJECT_ROOT_DIR}/logs"
BUILD_LOG_FILE="${LOG_DIR}/build_log.txt"
TRADE_LOG_FILE="${LOG_DIR}/trade_log.txt"

# 创建日志目录（如果不存在）
mkdir -p "$LOG_DIR"

# # 重定向所有输出到build_log.txt
# exec > "$BUILD_LOG_FILE" 2>&1

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
cmake ..  || { echo "CMake configuration failed"; exit 1; }

# 编译项目
echo "====== Building project... ======"
make  || { echo "Compilation failed"; exit 1; }

echo "====== Running DataLoaderTest... ======"
cd "test" || exit
./DataLoaderTest || { echo "DataLoaderTest Execution failed";}
./PortfolioManagerTest || { echo "PortfolioManagerTest Execution failed"; }
./TradeExecutorTest || { echo "TradeExecutorTest Execution failed"; }
./StatisticsModuleTest || { echo "StatisticsModuleTest Execution failed"; }
./StrategyTest || { echo "StrategyTest Execution failed"; }
cd ..

# 运行编译好的程序
echo "====== Running BackTestDemo... ======"
./BackTestDemo "$TRADE_LOG_FILE" "$DATA_FILE" | tee "$TRADE_LOG_FILE" || { echo "Execution failed"; exit 1; }

# 回到初始目录
cd "$PROJECT_ROOT_DIR" || exit
