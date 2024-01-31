#include "StatisticsModule.h"
#include <numeric>
#include <cmath>

StatisticsModule::StatisticsModule() {}

std::vector<double> StatisticsModule::calculateReturnsCurve(const std::vector<double>& priceData) {
    std::vector<double> returns;
    for (size_t i = 1; i < priceData.size(); ++i) {
        returns.push_back((priceData[i] - priceData[i - 1]) / priceData[i - 1]);
    }
    return returns;
}

double StatisticsModule::calculateInformationCoefficient(const std::vector<double>& forecasts, const std::vector<double>& actuals) {
    if (forecasts.size() != actuals.size() || forecasts.empty()) {
        return std::numeric_limits<double>::quiet_NaN();  // 返回 NaN 作为错误指示
    }

    double meanForecast = std::accumulate(forecasts.begin(), forecasts.end(), 0.0) / forecasts.size();
    double meanActual = std::accumulate(actuals.begin(), actuals.end(), 0.0) / actuals.size();

    double numerator = 0.0;
    double denominatorForecast = 0.0;
    double denominatorActual = 0.0;

    for (size_t i = 0; i < forecasts.size(); ++i) {
        numerator += (forecasts[i] - meanForecast) * (actuals[i] - meanActual);
        denominatorForecast += std::pow(forecasts[i] - meanForecast, 2);
        denominatorActual += std::pow(actuals[i] - meanActual, 2);
    }

    return numerator / std::sqrt(denominatorForecast * denominatorActual);
}

double StatisticsModule::calculateSharpeRatio(const std::vector<double>& returns, double riskFreeRate) {
    if (returns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double meanReturn = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double stdDeviation = std::sqrt(std::inner_product(returns.begin(), returns.end(), returns.begin(), 0.0) / returns.size() - std::pow(meanReturn, 2));

    return (meanReturn - riskFreeRate) / stdDeviation;
}

// 可以添加更多统计方法的实现
