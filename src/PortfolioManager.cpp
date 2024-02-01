#include "PortfolioManager.h"

PortfolioManager::PortfolioManager() : cash(100000) {  // 初始现金设置为 100,000，可根据需求调整
}

void PortfolioManager::updatePortfolio(const std::string& symbol, int quantity, double tradePrice) {
    updatePosition(symbol, quantity, tradePrice);
    updateCash(-quantity * tradePrice);
}

double PortfolioManager::getCash() const {
    return cash;
}

double PortfolioManager::getTotalValue() const {
    double totalValue = cash;
    for (const auto& [symbol, position] : positions) {
        totalValue += position.quantity * position.averageCost;  // 假设以平均成本计算总价值
    }
    return totalValue;
}

Position PortfolioManager::getPosition(const std::string& symbol) const {
    if (positions.find(symbol) != positions.end()) {
        return positions.at(symbol);
    }
    return Position{0, 0.0};
}

void PortfolioManager::updatePosition(const std::string& symbol, int quantity, double tradePrice) {
    Position& position = positions[symbol];
    double totalCost = position.averageCost * position.quantity + tradePrice * quantity;
    position.quantity += quantity;
    position.averageCost = (position.quantity != 0) ? totalCost / position.quantity : 0;
}

void PortfolioManager::updateCash(double amount) {
    cash += amount;
}

