#pragma once

#include "Timestamp.h"
#include "noncopyable.h"
#include "CurrentThread.h"

#include <functional>
#include <atomic>
#include <memory>
#include <vector>
#include <mutex>

/**
    事件循环, 包含了Channel和Poller(epoll抽象类)
*/
class Channel;
class Poller;

class EventLoop: muduo::noncopyable
{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    //开启事件循环
    void loop();
    //退出事件循环
    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    //在当前loop中执行回调
    void runInLoop(Functor cb);
    //把回调放入队列, 唤醒loop所在的线程执行回调
    void queueInLoop(Functor cb);

    //唤醒loop所在的线程
    void wakeup();

    //通过EventLoop调用Poller的方法
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);

    //判断EventLoop对象是否在自己的线程里面
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
private:
    void handleRead();  //wakeup
    void doPendingFunctors();   //执行回调

    using ChannelList = std::vector<Channel*>;

    std::atomic_bool looping_;
    std::atomic_bool quit_;
    
    const pid_t threadId_;  //当前loop所在线程的id
    Timestamp pollReturnTime_;  //poller返回发生时间的channels的时间点
    std::unique_ptr<Poller> poller_;

    int wakeupFd_;  //当mainloop获取一个新用户的channel, 通过轮询选择一个subloop, 通过该成员通知唤醒subloop处理
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_;

    std::atomic_bool callingPendingFunctors_;   //表示当前loop是否有需要执行的回调操作
    std::vector<Functor> pendingFunctors_;  //存储loop需要执行的所有回调操作
    std::mutex mutex_;  //用来保护vector容器的线程安全
};