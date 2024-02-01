#include "StatisticsModule.h"
#include <gtest/gtest.h>
#include <vector>

class StatisticsModuleTest : public ::testing::Test {
protected:
    StatisticsModule statsModule;
};

// 测试计算收益曲线
TEST_F(StatisticsModuleTest, CalculateReturnsCurve) {
    std::vector<double> priceData = {100, 105, 110};
    auto returns = statsModule.calculateReturnsCurve(priceData);
    EXPECT_NEAR(returns[0], 0.05, 1e-6);  // 第一天的收益率
    EXPECT_NEAR(returns[1], 0.047619, 1e-6);  // 第二天的收益率
}

// 测试计算信息系数
TEST_F(StatisticsModuleTest, CalculateInformationCoefficient) {
    std::vector<double> forecasts = {0.1, 0.2, 0.3};
    std::vector<double> actuals = {0.15, 0.25, 0.35};
    double ic = statsModule.calculateInformationCoefficient(forecasts, actuals);
    EXPECT_NEAR(ic, 1.0, 1e-6); 
}

// 测试空数据时抛出异常
TEST_F(StatisticsModuleTest, CalculateSharpeRatioEmptyData) {
    std::vector<double> periodReturns; // 空的收益率数据
    EXPECT_THROW({
        statsModule.calculateSharpeRatio(periodReturns, 'D', 0.01);
    }, std::invalid_argument);
}

// 测试不同频率下的年化因子
TEST_F(StatisticsModuleTest, CalculateSharpeRatioDifferentFrequencies) {
    std::vector<double> periodReturns = {0.05, 0.02, -0.01}; 
    double rfr = 0.01; // 假设年化无风险利率为1%
    double dailySharpeRatio = statsModule.calculateSharpeRatio(periodReturns, 'D', rfr);
    double monthlySharpeRatio = statsModule.calculateSharpeRatio(periodReturns, 'M', rfr);
    double quarterlySharpeRatio = statsModule.calculateSharpeRatio(periodReturns, 'Q', rfr);
    double annualSharpeRatio = statsModule.calculateSharpeRatio(periodReturns, 'A', rfr);

    // 根据频率的不同，预期的夏普比率会有所不同
    EXPECT_NE(dailySharpeRatio, monthlySharpeRatio);
    EXPECT_NE(monthlySharpeRatio, quarterlySharpeRatio);
    EXPECT_NE(quarterlySharpeRatio, annualSharpeRatio);
}

// 测试计算最大回撤
TEST_F(StatisticsModuleTest, CalculateMaxDrawdown) {
    std::vector<double> equityCurve = {100, 110, 105, 115};
    double maxDrawdown = statsModule.calculateMaxDrawdown(equityCurve);
    EXPECT_NEAR(maxDrawdown, 0.0454545, 1e-6);  // 最大回撤
}

// 测试计算 Beta
TEST_F(StatisticsModuleTest, CalculateBeta) {
    std::vector<double> stockReturns = {0.02, 0.03, 0.04};
    std::vector<double> benchmarkReturns = {0.01, 0.02, 0.03};
    double beta = statsModule.calculateBeta(stockReturns, benchmarkReturns);
    EXPECT_NEAR(beta, 1.0, 1e-6);  
}

// 测试计算 Alpha
TEST_F(StatisticsModuleTest, CalculateAlpha) {
    std::vector<double> stockReturns = {0.02, 0.03, 0.04};
    std::vector<double> benchmarkReturns = {0.01, 0.02, 0.03};
    double beta = 1.0;  // 假设 Beta 为 1.0
    double alpha = statsModule.calculateAlpha(stockReturns, benchmarkReturns, 0.01, beta);
    EXPECT_NEAR(alpha, 0.01, 1e-6);  
}

