## BackTest


### 文件结构
main.cpp - 程序入口和框架集成。

DataLoader.h / DataLoader.cpp - 负责从CSV或数据库加载股票数据。

Strategy.h / Strategy.cpp - 定义交易策略逻辑，生成买卖信号。

TradeExecutor.h / TradeExecutor.cpp - 根据交易策略执行买卖操作。

PortfolioManager.h / PortfolioManager.cpp - 管理资产和头寸。

StatisticsModule.h / StatisticsModule.cpp - 计算统计指标。

### 运行流程
```
cd BackTest
./run_project.sh
```

### 注意
- 1. data下数据均为随机生成，未考虑非交易日的跳过，仅供测试使用
- 2. 纯demo,十分粗糙，仅供参考