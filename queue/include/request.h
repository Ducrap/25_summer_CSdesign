#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ctime>

//请求的优先级
enum class Priority{
    low,        //可推迟件
    standard,   //标准件
    high        //急件
};

//请求的结构体
struct request
{
    int request_ID;         //请求号
    std::string user_ID;    //用户ID
    std::string expressID;  //快递单号
    Priority priority;      //优先级
    time_t requestTime;     //请求时间，用于同优先级下的排列
                            //std::string& :字符串传递引用，避免拷贝开销
    request(int id,const std::string& UID,const std::string& EID,Priority p,time_t t)
        : request_ID(id),user_ID(UID),expressID(EID),priority(p),requestTime(t){}
//
    bool operator<(const request& other) const{
        if(priority != other.priority)
            return priority < other.priority;
        return requestTime > other.requestTime;
    }

};

#endif
