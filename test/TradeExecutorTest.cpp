#include "TradeExecutor.h"
#include <gtest/gtest.h>

class TradeExecutorTest : public ::testing::Test {
protected:
    TradeExecutor executor;

    void SetUp() override {
        // 设置初始交易参数
        executor.setTradeParameters(100.0, 10);  // 假设价格为 100，数量为 10
    }
};

// 测试设置交易参数
TEST_F(TradeExecutorTest, SetTradeParameters) {
    // 更新交易参数
    executor.setTradeParameters(150.0, 5);
  
}

// 测试执行交易
TEST_F(TradeExecutorTest, ExecuteTrade) {
    // 测试买入
    TradeResult buyResult = executor.executeTrade(Signal::Buy);
    EXPECT_TRUE(buyResult.success);
    EXPECT_EQ(buyResult.message, "Executed Buy Order");

    // 测试卖出
    TradeResult sellResult = executor.executeTrade(Signal::Sell);
    EXPECT_TRUE(sellResult.success);
    EXPECT_EQ(sellResult.message, "Executed Sell Order");

    // 测试持有
    TradeResult holdResult = executor.executeTrade(Signal::Hold);
    EXPECT_TRUE(holdResult.success);
    EXPECT_EQ(holdResult.message, "No Action Taken");
}

// 测试交易历史记录
TEST_F(TradeExecutorTest, TradeHistory) {
    executor.executeTrade(Signal::Buy);
    executor.executeTrade(Signal::Sell);

    const auto& history = executor.getTradeHistory();
    EXPECT_EQ(history.size(), 2);  // 应该有两条记录

    // 检查第一条记录是否为买入
    EXPECT_EQ(history[0].signal, Signal::Buy);
    EXPECT_EQ(history[0].price, 100.0);
    EXPECT_EQ(history[0].quantity, 10);

    // 检查第二条记录是否为卖出
    EXPECT_EQ(history[1].signal, Signal::Sell);
    EXPECT_EQ(history[1].price, 100.0);
    EXPECT_EQ(history[1].quantity, 10);
}
