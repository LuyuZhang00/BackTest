cmake_minimum_required(VERSION 3.10)  # 指定CMake的最小版本要求

project(TradingStrategyDemo)  # 定义项目名称

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)
include_directories(include/utils/)

# 添加源文件
add_executable(TradingStrategyDemo main.cpp
               src/DataLoader.cpp
               src/PortfolioManager.cpp
               src/StatisticsModule.cpp
               src/Strategy.cpp
               src/TradeExecutor.cpp
               src/utils/timestamp.cpp
               )
