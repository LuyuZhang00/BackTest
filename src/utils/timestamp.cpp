#include "timestamp.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm tmTime = *std::localtime(&currentTime);
    std::stringstream timestamp;
    timestamp << std::put_time(&tmTime, "%Y-%m-%d %H:%M:%S");

    return "[" + timestamp.str() + "]  ";
}
