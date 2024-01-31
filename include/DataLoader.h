#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>

// 股票数据的结构，可以根据需求调整
struct StockData {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    long volume;
};

class DataLoader {
public:
    DataLoader();
    std::vector<StockData> loadData(const std::string& source);

private:
    std::vector<StockData> loadFromCSV(const std::string& filename);
    std::vector<StockData> loadFromDatabase(const std::string& connectionString);
};

#endif // DATALOADER_H