#include "StatisticsModule.h"
#include "PortfolioManager.h"  // 这将包含 Position 结构的定义

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
    double variance = std::inner_product(returns.begin(), returns.end(), returns.begin(), 0.0) / returns.size() - std::pow(meanReturn, 2);
    double stdDeviation = std::sqrt(variance);

    return (meanReturn - riskFreeRate) / stdDeviation;
}


double StatisticsModule::calculateMaxDrawdown(const std::vector<double>& equityCurve) {
    double peak = -std::numeric_limits<double>::infinity();
    double maxDrawdown = 0.0;

    for (double value : equityCurve) {
        if (value > peak) {
            peak = value;
        }
        double drawdown = (peak - value) / peak;
        if (drawdown > maxDrawdown) {
            maxDrawdown = drawdown;
        }
    }

    return maxDrawdown;
}

double StatisticsModule::calculateBeta(const std::vector<double>& stockReturns, const std::vector<double>& benchmarkReturns) {
    if (stockReturns.size() != benchmarkReturns.size() || stockReturns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();  // 返回 NaN 作为错误指示
    }

    double meanStock = std::accumulate(stockReturns.begin(), stockReturns.end(), 0.0) / stockReturns.size();
    double meanBenchmark = std::accumulate(benchmarkReturns.begin(), benchmarkReturns.end(), 0.0) / benchmarkReturns.size();

    double covariance = 0.0;
    double variance = 0.0;

    for (size_t i = 0; i < stockReturns.size(); ++i) {
        covariance += (stockReturns[i] - meanStock) * (benchmarkReturns[i] - meanBenchmark);
        variance += std::pow(benchmarkReturns[i] - meanBenchmark, 2);
    }

    return covariance / variance;
}

double StatisticsModule::calculateAlpha(const std::vector<double>& stockReturns, const std::vector<double>& benchmarkReturns, double riskFreeRate, double beta) {
    if (stockReturns.size() != benchmarkReturns.size() || stockReturns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();  // 返回 NaN 作为错误指示
    }

    double meanStock = std::accumulate(stockReturns.begin(), stockReturns.end(), 0.0) / stockReturns.size();
    double meanBenchmark = std::accumulate(benchmarkReturns.begin(), benchmarkReturns.end(), 0.0) / benchmarkReturns.size();

    return (meanStock - riskFreeRate) - beta * (meanBenchmark - riskFreeRate);
}

double StatisticsModule::calculateAnnualizedReturn(const std::vector<double>& returns) {
    double compoundedReturn = std::accumulate(returns.begin(), returns.end(), 1.0, std::multiplies<double>());
    return std::pow(compoundedReturn, 1.0 / returns.size()) - 1.0;
}

double StatisticsModule::calculateVolatility(const std::vector<double>& returns) {
    double mean = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double sq_sum = std::inner_product(returns.begin(), returns.end(), returns.begin(), 0.0);
    return std::sqrt(sq_sum / returns.size() - mean * mean);
}

double StatisticsModule::calculateSortinoRatio(const std::vector<double>& returns, double riskFreeRate) {
    double meanReturn = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    std::vector<double> downsideReturns;

    std::copy_if(returns.begin(), returns.end(), std::back_inserter(downsideReturns),
                 [meanReturn](double r) { return r < meanReturn; });

    double downsideRisk = calculateVolatility(downsideReturns);
    return (meanReturn - riskFreeRate) / downsideRisk;
}

double StatisticsModule::calculateCalmarRatio(const std::vector<double>& returns, double maxDrawdown) {
    double annualizedReturn = calculateAnnualizedReturn(returns);
    return annualizedReturn / maxDrawdown;
}

double StatisticsModule::calculateValueAtRisk(const std::vector<double>& returns, double confidenceLevel) {
    std::vector<double> sortedReturns = returns;
    std::sort(sortedReturns.begin(), sortedReturns.end());
    size_t index = (1.0 - confidenceLevel) * sortedReturns.size();
    return sortedReturns[index];
}

double StatisticsModule::calculateCVaR(const std::vector<double>& returns, double confidenceLevel) {
    double VaR = calculateValueAtRisk(returns, confidenceLevel);
    std::vector<double> lossesBeyondVaR;

    std::copy_if(returns.begin(), returns.end(), std::back_inserter(lossesBeyondVaR),
                 [VaR](double r) { return r < VaR; });

    return std::accumulate(lossesBeyondVaR.begin(), lossesBeyondVaR.end(), 0.0) / lossesBeyondVaR.size();
}

double StatisticsModule::calculateWinRate(const std::vector<double>& trades) {
    int wins = std::count_if(trades.begin(), trades.end(), [](double trade) { return trade > 0; });
    return static_cast<double>(wins) / trades.size();
}

double StatisticsModule::calculateProfitLossRatio(const std::vector<double>& trades) {
    double totalProfit = std::accumulate(trades.begin(), trades.end(), 0.0, 
                                         [](double sum, double trade) { return trade > 0 ? sum + trade : sum; });
    double totalLoss = std::accumulate(trades.begin(), trades.end(), 0.0, 
                                       [](double sum, double trade) { return trade < 0 ? sum + trade : sum; });
    int numProfits = std::count_if(trades.begin(), trades.end(), [](double trade) { return trade > 0; });
    int numLosses = trades.size() - numProfits;

    double avgProfit = numProfits > 0 ? totalProfit / numProfits : 0;
    double avgLoss = numLosses > 0 ? totalLoss / numLosses : 0;

    return avgLoss != 0 ? avgProfit / std::abs(avgLoss) : std::numeric_limits<double>::infinity();
}

double StatisticsModule::calculateConcentrationOfHoldings(const std::map<std::string, Position>& positions) {
    double totalValue = std::accumulate(positions.begin(), positions.end(), 0.0,
                                        [](double sum, const auto& p) { return sum + p.second.quantity * p.second.averageCost; });
    double largestPosition = std::max_element(positions.begin(), positions.end(),
                                              [](const auto& a, const auto& b) { return a.second.quantity * a.second.averageCost < b.second.quantity * b.second.averageCost; })->second.quantity * positions.begin()->second.averageCost;

    return totalValue > 0 ? largestPosition / totalValue : 0;
}

double StatisticsModule::calculateSharpeTreynorRatio(const std::vector<double>& returns, double riskFreeRate, double beta) {
    double excessReturn = calculateAnnualizedReturn(returns) - riskFreeRate;
    return beta != 0 ? excessReturn / beta : std::numeric_limits<double>::infinity();
}

double StatisticsModule::calculateOmegaRatio(const std::vector<double>& returns, double threshold) {
    double gain = std::accumulate(returns.begin(), returns.end(), 0.0, 
                                  [threshold](double sum, double r) { return r > threshold ? sum + (r - threshold) : sum; });
    double loss = std::accumulate(returns.begin(), returns.end(), 0.0, 
                                  [threshold](double sum, double r) { return r < threshold ? sum + (threshold - r) : sum; });

    return loss != 0 ? gain / loss : std::numeric_limits<double>::infinity();
}

double StatisticsModule::calculateActiveReturn(const std::vector<double>& portfolioReturns, const std::vector<double>& benchmarkReturns) {
    return calculateAnnualizedReturn(portfolioReturns) - calculateAnnualizedReturn(benchmarkReturns);
}

double StatisticsModule::calculateInformationRatio(const std::vector<double>& portfolioReturns, const std::vector<double>& benchmarkReturns) {
    std::vector<double> activeReturns(portfolioReturns.size());
    std::transform(portfolioReturns.begin(), portfolioReturns.end(), benchmarkReturns.begin(), activeReturns.begin(), std::minus<double>());

    double meanActiveReturn = std::accumulate(activeReturns.begin(), activeReturns.end(), 0.0) / activeReturns.size();
    double stdDeviation = calculateVolatility(activeReturns);

    return meanActiveReturn / stdDeviation;
}
