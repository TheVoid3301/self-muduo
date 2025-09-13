#pragma once

#include "EventLoop.h"
#include "noncopyable.h"
#include "Timestamp.h"

#include <functional>
#include <memory>

class EventLoop;
/**
    EventLoop -> Channel, Poller
    Channel, 封装了sockfd和感兴趣的event, 如EPOLLIN
    还保存了poller返回的具体时间
*/
class Channel: muduo::noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    //fd得到poller通知后, 处理事件, 调用相应的回调方法
    void handleEvent(Timestamp receiveTime);

    //设置回调函数对象
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    //防止当channel被手动remove, channel还在执行回调函数
    void tie(const std::shared_ptr<void> &);

    int fd() const { return fd_; }
    int events() const {return events_; }
    int set_revent(int revt) { return revents_; }

    //设置fd对应的事件状态
    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() {events_ = kNoneEvent; update(); }

    //返回fd当前的事件状态
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    bool isReading() const { return events_ & kReadEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }
    EventLoop* ownerLoop() {return loop_; }
    void remove();

private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_; //事件循环
    const int fd_; //fd
    int events_; //注册的事件
    int revents_; //poller返回的发生事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    /**
        Channel能够获知fd最终发生的具体事件
    */
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};