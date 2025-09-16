#pragma once

#include "noncopyable.h"
#include "EventLoop.h"

#include <functional>

class EventLoopThreadPool: muduo::noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
private:

    EventLoop* baseLoop_;
};