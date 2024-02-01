# 查找并加载 Google Test 的配置
find_package(GTest REQUIRED)

# 包含 Google Test 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

# 定义测试目标
add_executable(DataLoaderTest DataLoaderTest.cpp test_main.cpp)
add_executable(PortfolioManagerTest PortfolioManagerTest.cpp test_main.cpp)

# 链接 Google Test 库和项目库
target_link_libraries(DataLoaderTest ${GTEST_LIBRARIES} pthread BackTestLib)
target_link_libraries(PortfolioManagerTest ${GTEST_LIBRARIES} pthread BackTestLib)

# 添加测试到 CTest
add_test(NAME DataLoaderTest COMMAND DataLoaderTest)
add_test(NAME PortfolioManagerTest COMMAND PortfolioManagerTest)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -V)