#include "EventLoop.h"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>

//防止一个线程创建多个EventLoop
__thread EventLoop* t_loopInThisThread = nullptr;

//定义默认PollerIO复用接口的超时时间
const int kPollTimeMs = 10000;

int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
}