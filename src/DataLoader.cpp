#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

DataLoader::DataLoader() {
    // 构造函数内容，如果有必要
}

std::vector<StockData> DataLoader::loadData(const std::string& source) {
    if (source.find(".csv") != std::string::npos) {
        return loadFromCSV(source);
    }
    // 可以增加更多条件，用于从不同的数据源加载数据
    throw std::runtime_error("Unsupported data source");
}

std::vector<StockData> DataLoader::loadFromCSV(const std::string& filename) {
    std::vector<StockData> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (std::getline(file, line)) {
        std::istringstream s(line);
        StockData stockData;
        std::string field;

        // 解析 CSV 的每一行
        std::getline(s, stockData.date, ',');
        std::getline(s, field, ','); stockData.open = std::stod(field);
        std::getline(s, field, ','); stockData.high = std::stod(field);
        std::getline(s, field, ','); stockData.low = std::stod(field);
        std::getline(s, field, ','); stockData.close = std::stod(field);
        std::getline(s, field, ','); stockData.volume = std::stol(field);

        data.push_back(stockData);
    }

    return data;
}

// 用于从数据库加载数据的函数，暂时留空
std::vector<StockData> DataLoader::loadFromDatabase(const std::string& connectionString) {
    // 实现数据库加载逻辑
    return std::vector<StockData>(); // 暂时返回空向量
}

// 用于从交易所加载数据的函数，暂时留空
std::vector<StockData> DataLoader::loadFromExchange(const std::string& exchange, const std::string& ticker) {
    // 实现交易所加载逻辑
    return std::vector<StockData>(); // 暂时返回空向量
}