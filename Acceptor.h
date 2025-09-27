#pragma once

#include "Socket.h"
#include "Channel.h"

#include "noncopyable.h"
#include <functional>

class EventLoop;
class InetAddress;

class Acceptor: muduo::noncopyable
{
public:
    using newConnectionCallback = std::function<void(int sockfd, const InetAddress&)>;
    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const newConnectionCallback &cb) { newConnectionCallback_ = std::move(cb); }
    bool listening() const { return listening_; }
    void listen();
private:
    void handleRead();

    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    newConnectionCallback newConnectionCallback_;
    bool listening_;
};