#pragma once

#include "noncopyable.h"
#include "EventLoop.h"
#include "Thread.h"

#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>

class EventLoopThread: muduo::noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(), const std::string& name = std::string());
    ~EventLoopThread();

    EventLoop* startLoop();
private:
    void threadFunc();

    EventLoop* loop_;
    bool exiting_;
    Thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallback callback_;
};