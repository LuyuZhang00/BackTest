#include <iostream>
#include "DataLoader.h"
#include "Strategy.h"
#include "TradeExecutor.h"
#include "PortfolioManager.h"
#include "StatisticsModule.h"

int main() {
    DataLoader dataLoader;
    Strategy strategy(5, 20);  // 使用5天和20天的移动平均
    TradeExecutor executor;
    PortfolioManager portfolioManager;
    StatisticsModule statisticsModule;

    // 加载股票数据
    auto stockData = dataLoader.loadData("/home/zhangluyu/code/BackTest/data/stock_data.csv");

    std::vector<StockData> historicalData;
    std::vector<double> closingPrices;

    // 遍历股票数据
    for (const auto& dayData : stockData) {
        historicalData.push_back(dayData);
        closingPrices.push_back(dayData.close);

        if (historicalData.size() >= strategy.getLongWindow()) {
            // 生成交易信号
            auto signal = strategy.generateSignal(historicalData);

            // 执行交易
            executor.setTradeParameters(dayData.close, 100); // 假设交易100股
            auto tradeResult = executor.executeTrade(signal);

            // 输出交易结果
            std::cout << "Trade on " << dayData.date << " - Signal: " << static_cast<int>(signal)
                      << ", Result: " << tradeResult.message << std::endl;

            // 更新投资组合
            if (tradeResult.success) {
                // 假设每个交易都是基于单一股票的
                // 这里需要根据交易结果更新投资组合
                portfolioManager.updatePortfolio("STOCK_TICKER", 100, dayData.close);
            }
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
