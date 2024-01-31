#ifndef STATISTICSMODULE_H
#define STATISTICSMODULE_H

#include <vector>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>

struct Position {
    int quantity;
    double averageCost;
};


class StatisticsModule {
public:
    StatisticsModule();

    // 计算收益曲线
    std::vector<double> calculateReturnsCurve(const std::vector<double>& priceData);

    // 计算信息系数 (IC)
    double calculateInformationCoefficient(const std::vector<double>& forecasts, const std::vector<double>& actuals);

    // 计算夏普比率
    double calculateSharpeRatio(const std::vector<double>& returns, double riskFreeRate = 0.0);

    // 计算最大回撤
    double calculateMaxDrawdown(const std::vector<double>& equityCurve);

    // 计算贝塔系数
    double calculateBeta(const std::vector<double>& stockReturns, const std::vector<double>& benchmarkReturns);

    // 计算阿尔法系数
    double calculateAlpha(const std::vector<double>& stockReturns, const std::vector<double>& benchmarkReturns, double riskFreeRate, double beta);

    // 计算年化收益率
    double calculateAnnualizedReturn(const std::vector<double>& returns);

    // 计算年化波动率
    double calculateVolatility(const std::vector<double>& returns);

    // 计算索提诺比率
    double calculateSortinoRatio(const std::vector<double>& returns, double riskFreeRate = 0.0);

    // 计算Calmar比率
    double calculateCalmarRatio(const std::vector<double>& returns, double maxDrawdown);

    // 计算VaR
    double calculateValueAtRisk(const std::vector<double>& returns, double confidenceLevel);

    // 计算CVaR
    double calculateCVaR(const std::vector<double>& returns, double confidenceLevel);
    // 计算胜率
    double calculateWinRate(const std::vector<double>& trades);

    // 计算盈亏比
    double calculateProfitLossRatio(const std::vector<double>& trades);

    // 计算持仓集中度
    double calculateConcentrationOfHoldings(const std::map<std::string, Position>& positions);

    // 计算Sharpe-Treynor Ratio
    double calculateSharpeTreynorRatio(const std::vector<double>& returns, double riskFreeRate, double beta);

    // 计算Omega比率
    double calculateOmegaRatio(const std::vector<double>& returns, double threshold);

    // 计算主动收益
    double calculateActiveReturn(const std::vector<double>& portfolioReturns, const std::vector<double>& benchmarkReturns);

    // 计算信息比率
    double calculateInformationRatio(const std::vector<double>& portfolioReturns, const std::vector<double>& benchmarkReturns);

};

#endif // STATISTICSMODULE_H
