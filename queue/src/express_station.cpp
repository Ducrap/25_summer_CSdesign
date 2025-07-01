// express_station.cpp
#include "express_station.h"
#include <iostream>
#include <thread>

void ExpressStation::addRequest(const request& req) {
    {
        std::lock_guard<std::mutex> lock(stationMutex);
        requestQueue.enqueue(req);
        std::cout << "请求已添加: 用户 " << req.user_ID << std::endl;
    }
    cv.notify_one(); // 通知处理线程
}

void ExpressStation::processRequests() {
    while (true) {
        std::unique_lock<std::mutex> lock(stationMutex);
        
        // 等待条件：队列非空且有空余容量
        cv.wait(lock, [this]() {
            return !requestQueue.isEmpty() && currentCapacity < MAX_CAPACITY;
        });

        // 取出请求并占用容量
        request req = requestQueue.dequeue();
        currentCapacity++;
        lock.unlock();

        // 模拟取件过程
        std::cout << "处理中: 用户 " << req.user_ID 
                  << " (优先级: " << static_cast<int>(req.priority) << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 取件完成，释放容量
        lock.lock();
        currentCapacity--;
        cv.notify_all(); // 通知其他等待的请求
    }
}

int ExpressStation::getCurrentCapacity() const {
    std::lock_guard<std::mutex> lock(stationMutex);
    return currentCapacity;
}
