#pragma once

#include "noncopyable.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "EventLoopThreadPool.h"

#include <functional>
#include <memory>

class TcpServer: muduo::noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;

private:
    EventLoop *loop_;
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;
};