#ifndef TRADEEXECUTOR_H
#define TRADEEXECUTOR_H

#include "Strategy.h"
#include <vector>
#include <string>

// 交易结果的结构
struct TradeResult {
    bool success;
    std::string message;
};

// 交易历史记录的结构
struct TradeRecord {
    Signal signal;
    std::string time;
    double price;
    int quantity;
    std::string result;
};

class TradeExecutor {
public:
    TradeExecutor();
    void setTradeParameters(double price, int quantity);
    TradeResult executeTrade(Signal signal);
    const std::vector<TradeRecord>& getTradeHistory() const;

private:
    double tradePrice;
    int tradeQuantity;
    std::vector<TradeRecord> tradeHistory;

    // 私有方法，用于记录交易
    void recordTrade(Signal signal, const TradeResult& result);
};

#endif // TRADEEXECUTOR_H
