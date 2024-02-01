#include <iostream>
#include <fstream>

#include "DataLoader.h"
#include "Strategy.h"
#include "TradeExecutor.h"
#include "PortfolioManager.h"
#include "StatisticsModule.h"
#include "utils/timestamp.h"

int main(int argc, char* argv[]) {
    
    // 检查命令行参数数量
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <log_file_path> <data_file_path>" << std::endl;
        return 1;
    }
    
    std::string logFilePath = argv[1];
    std::string dataFilePath = argv[2];


    // 定义并打开日志文件
    std::ofstream logFile(logFilePath);
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file: " << logFilePath << std::endl;
        return 1;
    }

    DataLoader dataLoader;
    Strategy strategy(5, 20);  // 使用5天和20天的移动平均
    TradeExecutor executor;
    PortfolioManager portfolioManager;
    StatisticsModule statisticsModule;
    
    // 加载股票数据
    auto stockData = dataLoader.loadData(dataFilePath);
    

    std::vector<StockData> historicalData;
    std::vector<double> closingPrices;
    int sell_count = 0;
    int buy_count = 0;

    // 遍历股票数据
    for (const auto& dayData : stockData) {
        historicalData.push_back(dayData);
        closingPrices.push_back(dayData.close);

        if (historicalData.size() >= strategy.getLongWindow()) {
            // 生成交易信号
            auto signal = strategy.generateSignal(historicalData);

            if (signal == Signal::Buy) {
                buy_count++;
            } else if (signal == Signal::Sell) {
                sell_count++;
            }

            // 执行交易
            executor.setTradeParameters(dayData.close, 100); // 假设交易100股
            auto tradeResult = executor.executeTrade(signal);

            // 将交易结果写入日志文件和输出到终端
            std::string logEntry = getTimestamp() + "Trade on " + dayData.date + " - Signal: " + std::to_string(static_cast<int>(signal))
                                   + ", Result: " + tradeResult.message;
            logFile << logEntry << std::endl;
            std::cout << logEntry << std::endl;

            // 更新投资组合
            if (tradeResult.success) {
                // 假设每个交易都是基于单一股票的
                // 这里需要根据交易结果更新投资组合
                portfolioManager.updatePortfolio(dayData.symbol, 100, dayData.close);
            }
        }

    }


    // 计算并显示统计指标
    auto returnsCurve = statisticsModule.calculateReturnsCurve(closingPrices);
    double sharpeRatio = statisticsModule.calculateSharpeRatio(returnsCurve);
    double maxDrawdown = statisticsModule.calculateMaxDrawdown(closingPrices);
    double sortinoRatio = statisticsModule.calculateSortinoRatio(returnsCurve);

    // 显示结果
    std::cout << "========== summary ==========" << std::endl;
    std::cout << "sell_count:   " << sell_count << std::endl;
    std::cout << "buy_count:    " << buy_count << std::endl;
    std::cout << "Sharpe Ratio: " << sharpeRatio << std::endl;
    std::cout << "Max Drawdown: " << maxDrawdown << std::endl;
    std::cout << "Sortino Ratio: " << sortinoRatio << std::endl;

    // 关闭日志文件
    logFile.close();

    return 0;
}
