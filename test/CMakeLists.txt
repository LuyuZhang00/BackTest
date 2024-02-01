# 查找并加载 Google Test 的配置
find_package(GTest REQUIRED)

# 包含 Google Test 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

# 定义一个包含所有测试的列表
set(TESTS DataLoaderTest PortfolioManagerTest TradeExecutorTest StatisticsModuleTest StrategyTest)

# 为每个测试创建一个可执行文件和链接库
foreach(test ${TESTS})
    add_executable(${test} ${test}.cpp test_main.cpp)
    target_link_libraries(${test} ${GTEST_LIBRARIES} pthread BackTestLib)
    add_test(NAME ${test} COMMAND ${test})
endforeach()

# 添加一个自定义目标来运行所有测试
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -V)
