#include "Strategy.h"
#include <gtest/gtest.h>
#include <vector>

class StrategyTest : public ::testing::Test {
protected:
    Strategy strategy;

    StrategyTest() : strategy(5, 20) {}  // 假设短期窗口为 5 天，长期窗口为 20 天

    std::vector<StockData> createStockData(const std::vector<double>& prices) {
        std::vector<StockData> data;
        for (double price : prices) {
            StockData sd;
            sd.close = price;
            data.push_back(sd);
        }
        return data;
    }
};

// 测试生成交易信号
TEST_F(StrategyTest, GenerateSignal) {
    // 创建测试数据
    std::vector<StockData> testData = createStockData({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});

    // 期望买入信号：短期 MA > 长期 MA
    Signal signalBuy = strategy.generateSignal(testData);
    EXPECT_EQ(signalBuy, Signal::Buy);

    // 更新测试数据以反映预期的卖出信号：短期 MA < 长期 MA
    testData = createStockData({21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
    Signal signalSell = strategy.generateSignal(testData);
    EXPECT_EQ(signalSell, Signal::Sell);

    // 更新测试数据以反映预期的持有信号：短期 MA == 长期 MA
    testData = createStockData(std::vector<double>(40, 10));  // 40 天的价格都是 10
    Signal signalHold = strategy.generateSignal(testData);
    EXPECT_EQ(signalHold, Signal::Hold);
}

// 测试数据不足的情况
TEST_F(StrategyTest, InsufficientData) {
    // 创建不足长期窗口的测试数据
    std::vector<StockData> testData = createStockData({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    Signal signal = strategy.generateSignal(testData);
    EXPECT_EQ(signal, Signal::Hold);  // 数据不足时应该保持
}
