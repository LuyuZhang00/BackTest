# cmake_minimum_required(VERSION 3.10)  # 指定CMake的最小版本要求

# project(TradingStrategyDemo)  # 定义项目名称

# # 设置C++标准
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    DataLoader.cpp
    PortfolioManager.cpp
    StatisticsModule.cpp
    Strategy.cpp
    TradeExecutor.cpp
    utils/timestamp.cpp
)

# 创建一个名为 BackTestLib 的库
add_library(BackTestLib ${SOURCE_FILES})