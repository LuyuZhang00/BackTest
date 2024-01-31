#include "DataLoader.h"
#include "Strategy.h"
#include "TradeExecutor.h"
#include "PortfolioManager.h"
#include "StatisticsModule.h"

int main() {
    DataLoader dataLoader;
    Strategy strategy;
    TradeExecutor executor;
    PortfolioManager portfolioManager;
    StatisticsModule statisticsModule;

    // 数据加载
    auto data = dataLoader.loadData("stock_data.csv");

    // 策略执行
    for (const auto& dayData : data) {
        auto signal = strategy.generateSignal(dayData);
        auto tradeResult = executor.executeTrade(signal);
        portfolioManager.updatePortfolio(tradeResult);
    }

    // 统计分析
    auto returns = portfolioManager.getReturns();
    auto sharpeRatio = statisticsModule.calculateSharpeRatio(returns);

    // 输出结果
    std::cout << "Sharpe Ratio: " << sharpeRatio << std::endl;

    return 0;
}
