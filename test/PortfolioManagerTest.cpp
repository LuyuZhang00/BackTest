#include "PortfolioManager.h"
#include <gtest/gtest.h>

class PortfolioManagerTest : public ::testing::Test {
protected:
    PortfolioManager manager;

    void SetUp() override {
        // 这里可以设置一些初始状态
    }

    void TearDown() override {
        // 这里可以进行一些清理工作
    }
};

// 测试初始现金余额
TEST_F(PortfolioManagerTest, InitialCashBalance) {
    EXPECT_EQ(manager.getTotalValue(), 100000);  // 初始现金设为 100,000
}

// 测试更新投资组合
TEST_F(PortfolioManagerTest, UpdatePortfolio) {
    manager.updatePortfolio("AAPL", 100, 150);  // 假设买入 100 股 AAPL，每股 150
    std::cout << manager.getTotalValue() << std::endl;
    EXPECT_EQ(manager.getPosition("AAPL").quantity, 100);
    EXPECT_NEAR(manager.getPosition("AAPL").averageCost, 150, 1e-6);
    EXPECT_NEAR(manager.getTotalValue(), 100000 - 100 * 150, 1e-6);  // 总价值应减少
}

// 测试获取头寸信息
TEST_F(PortfolioManagerTest, GetPosition) {
    manager.updatePortfolio("AAPL", 10, 150);
    Position position = manager.getPosition("AAPL");
    EXPECT_EQ(position.quantity, 10);
    EXPECT_NEAR(position.averageCost, 150, 1e-6);
}

// 测试不存在的头寸
TEST_F(PortfolioManagerTest, GetNonExistentPosition) {
    Position position = manager.getPosition("XYZ");
    EXPECT_EQ(position.quantity, 0);
    EXPECT_EQ(position.averageCost, 0);
}

