#include "TradeExecutor.h"
#include <ctime>
#include <sstream>

TradeExecutor::TradeExecutor() : tradePrice(0.0), tradeQuantity(0) {}

void TradeExecutor::setTradeParameters(double price, int quantity) {
    tradePrice = price;
    tradeQuantity = quantity;
}

TradeResult TradeExecutor::executeTrade(Signal signal) {
    TradeResult result;

    // 以下代码需要根据您的实际交易接口进行调整
    switch (signal) {
        case Signal::Buy:
            // 买入逻辑
            result.success = true;
            result.message = "Executed Buy Order";
            break;

        case Signal::Sell:
            // 卖出逻辑
            result.success = true;
            result.message = "Executed Sell Order";
            break;

        case Signal::Hold:
            result.success = true;
            result.message = "No Action Taken";
            break;

        default:
            result.success = false;
            result.message = "Unknown Signal";
            break;
    }

    recordTrade(signal, result);
    return result;
}

const std::vector<TradeRecord>& TradeExecutor::getTradeHistory() const {
    return tradeHistory;
}

void TradeExecutor::recordTrade(Signal signal, const TradeResult& result) {
    TradeRecord record;
    record.signal = signal;

    // 获取当前时间
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::ctime(&now);
    record.time = ss.str();

    record.price = tradePrice;
    record.quantity = tradeQuantity;
    record.result = result.message;

    tradeHistory.push_back(record);
}
