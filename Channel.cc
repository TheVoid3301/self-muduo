#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

#include <memory>
#include <sys/epoll.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;


/**
    EventLoop: ChannelList, Poller
*/
Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
    , tied_(false)
{
}

Channel::~Channel()
{
}

void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj;
    tied_ = true;
}

/**
    当改变Channel所表示fd的events后, update负责在poller中更改fd对应的事件epoll_ctl
*/
void Channel::update()
{
    //通过Channel所属的EventLoop, 调用poller的相应方法, 注册fd的events事件
    loop_->updateChannel(this);
}

/**
    在Channel所属的EventLoop中, 把当前Channel删除
*/
void Channel::remove()
{
    loop_->removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
    if (tied_)
    {
        std::shared_ptr<void> guard = tie_.lock();
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

/**
    根据poller通知的具体事件, 由channel调用对应的回调
*/
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
    LOG_INFO("Channel handldEvent revents: %d", revents_);

    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (closeCallback_)
        {
            closeCallback_();
        }
    }

    if (revents_ & EPOLLERR)
    {
        if (errorCallback_)
        {
            errorCallback_();
        }
    }

    if (revents_ & (EPOLLIN | EPOLLPRI))
    {
        if (readCallback_)
        {
            readCallback_(receiveTime);
        }
    }

    if (revents_ & EPOLLOUT)
    {
        if (writeCallback_)
        {
            writeCallback_();
        }
    }
}