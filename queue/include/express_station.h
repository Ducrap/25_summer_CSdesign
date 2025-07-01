// express_station.h
#ifndef EXPRESS_STATION_H
#define EXPRESS_STATION_H

#include "queue.h"
#include <condition_variable>

class ExpressStation {
private:
    queue requestQueue;                // 优先级队列
    mutable std::mutex stationMutex;          // 互斥锁
    std::condition_variable cv;       // 条件变量
    int currentCapacity = 0;          // 当前站内人数
    const int MAX_CAPACITY = 5;       // 最大容量

public:
    // 添加请求并尝试处理
    void addRequest(const request& req);
    
    // 处理请求（内部循环）
    void processRequests();
    
    // 获取当前站内人数
    int getCurrentCapacity() const;
};

#endif