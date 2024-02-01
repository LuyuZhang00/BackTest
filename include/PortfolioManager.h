#ifndef PORTFOLIOMANAGER_H
#define PORTFOLIOMANAGER_H

#include <map>
#include <string>

// 定义股票头寸的结构
struct Position {
    int quantity;        // 持有数量
    double averageCost;  // 平均成本
};

class PortfolioManager {
public:
    PortfolioManager();

    // 更新投资组合
    void updatePortfolio(const std::string& symbol, int quantity, double tradePrice);

    // 获取投资组合的总价值
    double getTotalValue() const;

    // 获取指定股票
    Position getPosition(const std::string& symbol) const;

private:
    std::map<std::string, Position> positions;  // 持有的股票
    double cash;                                // 现金余额

    // 辅助方法，用于更新头寸和现金
    void updatePosition(const std::string& symbol, int quantity, double tradePrice);
    void updateCash(double amount);
};

#endif // PORTFOLIOMANAGER_H
