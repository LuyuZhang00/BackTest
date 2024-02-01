#include "DataLoader.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>

class DataLoaderTest : public ::testing::Test {
protected:
    // 设置测试用的 CSV 文件路径
    const std::string testCsvFile = "test_stock_data.csv";

    // 在每个测试前运行
    void SetUp() override {
        std::ofstream testFile(testCsvFile);
        testFile << "600519.SH,20230101,100,102,99,101,1000\n";
        testFile << "600519.SH,20230102,101,103,100,102,1500\n";
        testFile.close();
    }

    // 在每个测试后运行
    void TearDown() override {
        std::remove(testCsvFile.c_str());
    }
};

// 测试 DataLoader::loadFromCSV 方法
TEST_F(DataLoaderTest, LoadFromCSV) {
    DataLoader loader;
    auto data = loader.loadFromCSV(testCsvFile);

    // 预期读取了两行数据
    ASSERT_EQ(data.size(), 2);

    // 测试第一行数据
    EXPECT_EQ(data[0].date, "20230101");
    EXPECT_EQ(data[0].open, 100);
    EXPECT_EQ(data[0].high, 102);
    EXPECT_EQ(data[0].low, 99);
    EXPECT_EQ(data[0].close, 101);
    EXPECT_EQ(data[0].volume, 1000);

    // 测试第二行数据
    EXPECT_EQ(data[1].date, "20230102");
    EXPECT_EQ(data[1].open, 101);
    EXPECT_EQ(data[1].high, 103);
    EXPECT_EQ(data[1].low, 100);
    EXPECT_EQ(data[1].close, 102);
    EXPECT_EQ(data[1].volume, 1500);
}

// 测试 DataLoader::loadData 方法
TEST_F(DataLoaderTest, LoadDataCSV) {
    DataLoader loader;
    auto data = loader.loadData(testCsvFile);

    // 测试第一行数据
    EXPECT_EQ(data[0].date, "20230101");
    EXPECT_EQ(data[0].open, 100);
    EXPECT_EQ(data[0].high, 102);
    EXPECT_EQ(data[0].low, 99);
    EXPECT_EQ(data[0].close, 101);
    EXPECT_EQ(data[0].volume, 1000);

    // 测试第二行数据
    EXPECT_EQ(data[1].date, "20230102");
    EXPECT_EQ(data[1].open, 101);
    EXPECT_EQ(data[1].high, 103);
    EXPECT_EQ(data[1].low, 100);
    EXPECT_EQ(data[1].close, 102);
    EXPECT_EQ(data[1].volume, 1500);
}

// 测试 DataLoader::loadData 方法对不支持的数据源抛出异常
TEST_F(DataLoaderTest, LoadDataUnsupportedSource) {
    DataLoader loader;
    EXPECT_THROW(loader.loadData("unsupported_data_source.xyz"), std::runtime_error);
}
