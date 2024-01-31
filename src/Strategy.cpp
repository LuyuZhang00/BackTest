#include "Strategy.h"
#include <numeric>

Strategy::Strategy(int shortWindow, int longWindow)
    : shortWindow(shortWindow), longWindow(longWindow) {}

Signal Strategy::generateSignal(const std::vector<StockData>& historicalData) {
    if (historicalData.size() < longWindow) {
        return Signal::Hold;  // 数据不足时保持
    }

    double shortMA = calculateMovingAverage(historicalData, shortWindow);
    double longMA = calculateMovingAverage(historicalData, longWindow);

    if (shortMA > longMA) {
        return Signal::Buy;
    } else if (shortMA < longMA) {
        return Signal::Sell;
    } else {
        return Signal::Hold;
    }
}

double Strategy::calculateMovingAverage(const std::vector<StockData>& data, int window) {
    double sum = std::accumulate(data.end() - window, data.end(), 0.0,
                                 [](double a, const StockData& b) {
                                     return a + b.close;
                                 });
    return sum / window;
}
