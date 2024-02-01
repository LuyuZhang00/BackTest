#include "timestamp.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getTimestamp() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();
    auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tmTime = *std::localtime(&nowAsTimeT);
    std::stringstream timestamp;
    timestamp << std::put_time(&tmTime, "%Y-%m-%d %H:%M:%S");
    timestamp << '.' << std::setfill('0') << std::setw(3) << nowMs.count();

    return "[" + timestamp.str() + "]  ";
}
