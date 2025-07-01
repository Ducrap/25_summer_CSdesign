#include "queue.h"
#include <algorithm> // for std::sort

// 添加请求到队列（线程安全）
void queue::enqueue(const request& req) {
    std::lock_guard<std::mutex> lock(queueMutex);
    requestQueue.push(req);
}

// 从队列取出请求（线程安全）
request queue::dequeue() {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (requestQueue.empty()) {
        throw std::runtime_error("队列为空");
    }
    request req = requestQueue.top();
    requestQueue.pop();
    return req;
}

// 检查队列是否为空（线程安全）
bool queue::isEmpty() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return requestQueue.empty();
}

// 获取队列大小（线程安全）
size_t queue::size() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return requestQueue.size();
}

// 获取所有请求（用于显示，线程安全）
std::vector<request> queue::getAllrequests() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    std::vector<request> requests;
    
    // 复制一份临时队列以遍历
    auto tempQueue = requestQueue;
    while (!tempQueue.empty()) {
        requests.push_back(tempQueue.top());
        tempQueue.pop();
    }
    
    // 按优先级和时间排序（与优先队列顺序一致）
    std::sort(requests.begin(), requests.end());
    return requests;
}
