## BackTest
一个简单的回测demo

### 文件结构

```
.
├── CMakeLists.txt
├── data
│   ├── 600519.csv 
│   └── stock_data.csv      //股票数据
├── include
│   ├── DataLoader.h        //负责从CSV或数据库加载股票数据。
│   ├── PortfolioManager.h  //管理资产和头寸。
│   ├── StatisticsModule.h  //计算统计指标。
│   ├── Strategy.h          //定义交易策略逻辑，生成买卖信号。
│   ├── TradeExecutor.h     //根据交易策略执行买卖操作。
│   └── utils
│       └── timestamp.h      //时间戳转换工具。
├── logs
│   ├── build_log.txt       // 编译日志。
│   └── trade_log.txt       // 交易日志。
├── main.cpp                // 程序入口和框架集成。
├── README.md
├── run_project.sh          // 一键编译运行脚本。
├── src
│   ├── CMakeLists.txt
│   ├── DataLoader.cpp
│   ├── PortfolioManager.cpp
│   ├── StatisticsModule.cpp
│   ├── Strategy.cpp
│   ├── TradeExecutor.cpp
│   └── utils
│       └── timestamp.cpp
└── test                       // 单元测试。
    ├── CMakeLists.txt
    ├── DataLoaderTest.cpp
    ├── PortfolioManagerTest.cpp
    ├── StatisticsModuleTest.cpp
    ├── StrategyTest.cpp
    ├── test_main.cpp
    └── TradeExecutorTest.cpp
```

### 运行流程
```
cd BackTest
./run_project.sh
```

### 注意
- 1. 数据输出需要符合指定格式，具体见DataLoader.h
- 2. 纯demo,比较粗糙，仅供参考