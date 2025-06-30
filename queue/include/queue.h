#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <mutex>
#include <vector>
#include "request.h"

class queue{
private:
    std::priority_queue<request> requestQueue;
    std::mutex queueMutex;

public:
    //添加请求到队列
    void enqueue(const request& request);
    //从队列去除请求
    request dequeue();
    //检查队列是否为空
    bool isEmpty() const;
    //获取队列大小
    size_t size() const;
    //获取队列中所有请求_显示用
    std::vector<request> getAllrequests() const;
};

#endif
