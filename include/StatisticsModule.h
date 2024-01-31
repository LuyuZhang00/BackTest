#ifndef STATISTICSMODULE_H
#define STATISTICSMODULE_H

#include <vector>

class StatisticsModule {
public:
    StatisticsModule();

    // 计算收益曲线
    std::vector<double> calculateReturnsCurve(const std::vector<double>& priceData);

    // 计算信息系数 (IC)
    double calculateInformationCoefficient(const std::vector<double>& forecasts, const std::vector<double>& actuals);

    // 计算夏普比率
    double calculateSharpeRatio(const std::vector<double>& returns, double riskFreeRate = 0.0);

    // 可以添加更多统计方法
};

#endif // STATISTICSMODULE_H
