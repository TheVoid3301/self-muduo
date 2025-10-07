#include "TcpServer.h"
#include "Logger.h"

EventLoop* CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL("%s:%s:%d mainLoop is null! \n", __FILE__, __FUNCTION__, __LINE__);
    }
    return loop;
}

TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg, Option option)
    : loop_(CheckLoopNotNull(loop))
    , ipPort_(listenAddr.toIpPort())
    , name_(nameArg)
    , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))
    , threadPool_(new EventLoopThreadPool(loop, name_))
    , connectionCallback_(defaultConnectionCallback)
    , messageCallback_(defaultMessageCallback)
    , writeCompleteCallback_(defaultWriteCompleteCallback)
{

}

TcpServer::~TcpServer()
{

}

void TcpServer::setThreadNum(int numThreads)
{

}

void TcpServer::start()
{

}

void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{

}

void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{

}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{

}