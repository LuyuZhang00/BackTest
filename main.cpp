#include <iostream>
#include "DataLoader.h"
#include "Strategy.h"
#include "TradeExecutor.h"
#include "PortfolioManager.h"
#include "StatisticsModule.h"

int main() {
    DataLoader dataLoader;
    Strategy strategy(5, 20);  // 例如，使用5天和20天的移动平均
    TradeExecutor executor;
    PortfolioManager portfolioManager;
    StatisticsModule statisticsModule;

    // 加载股票数据
    auto stockData = dataLoader.loadData("/home/zhangluyu/code/BackTest/data/stock_data.csv");

    // 准备存储历史数据和收盘价
    std::vector<StockData> historicalData;
    std::vector<double> closingPrices;

    // 遍历股票数据
    for (const auto& dayData : stockData) {
        historicalData.push_back(dayData);
        closingPrices.push_back(dayData.close);

        // 确保历史数据有足够的天数来进行策略计算
        if (historicalData.size() >= strategy.getLongWindow()) {
            auto signal = strategy.generateSignal(historicalData);
            executor.setTradeParameters(dayData.close, 100); // 假设交易100股
            auto tradeResult = executor.executeTrade(signal);

            // 更新投资组合（这里可以根据交易结果调整）
            // portfolioManager.updatePortfolio(...);
        }
    }

    // 计算并显示统计指标
    auto returnsCurve = statisticsModule.calculateReturnsCurve(closingPrices);
    double sharpeRatio = statisticsModule.calculateSharpeRatio(returnsCurve);

    // 假设以下方法已在 StatisticsModule 中实现
    double maxDrawdown = statisticsModule.calculateMaxDrawdown(returnsCurve);
    double annualizedReturn = statisticsModule.calculateAnnualizedReturn(returnsCurve);
    double sortinoRatio = statisticsModule.calculateSortinoRatio(returnsCurve);

    // 显示结果
    std::cout << "Sharpe Ratio: " << sharpeRatio << std::endl;
    std::cout << "Max Drawdown: " << maxDrawdown << std::endl;
    std::cout << "Annualized Return: " << annualizedReturn << std::endl;
    std::cout << "Sortino Ratio: " << sortinoRatio << std::endl;

    return 0;
}
