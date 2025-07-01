#include "express_station.h"
#include <thread>

int main() {
    ExpressStation station;
    
    // 启动处理线程
    std::thread processor(&ExpressStation::processRequests, &station);

    // 模拟用户请求
    station.addRequest({1, "U1001", "EXP001", Priority::low, time(nullptr)});
    station.addRequest({2, "U1002", "EXP002", Priority::high, time(nullptr)});
    station.addRequest({3, "U1003", "EXP003", Priority::standard, time(nullptr)});

    // 主线程继续添加请求
    std::this_thread::sleep_for(std::chrono::seconds(1));
    station.addRequest({4, "U1004", "EXP004", Priority::high, time(nullptr)});

    processor.join(); // 等待线程结束
    return 0;
}
