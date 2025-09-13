#pragma once

#include "EventLoop.h"
#include "noncopyable.h"
#include "Timestamp.h"

#include <unordered_map>
#include <vector>

class Channel;
class EventLoop;

/**
    多路事件分发器的IO复用模块
*/
class Poller: muduo::noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop* loop);
    virtual ~Poller() = default;

    /**
        给所有IO复用, 保留统一的接口
    */
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;

    bool hasChannel(Channel* channel) const;

    /**
        EventLoop通过该接口获取默认的IO复用的具体实现
    */
    static Poller* newDefaultPoller(EventLoop* loop);
protected:
    //保存fd和对应channel的映射
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;
private:
    EventLoop* ownerLoop_;
};