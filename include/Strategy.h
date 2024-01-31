#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "DataLoader.h"  // 引入 StockData 结构

enum class Signal { Buy, Sell, Hold };  // 交易信号枚举

class Strategy {
public:
    Strategy(int shortWindow, int longWindow);

    Signal generateSignal(const std::vector<StockData>& historicalData);

    int getLongWindow() const; // 获取长期移动平均的窗口大小

private:
    int shortWindow;
    int longWindow;

    double calculateMovingAverage(const std::vector<StockData>& data, int window);
};

#endif // STRATEGY_H
