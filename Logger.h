#pragma once
#include <string>

#include "noncopyable.h"

#define LOG_INFO(LogmsgFormat, ...) \
    do \
    { \
        Logger::getInstance().setLogLever(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, sizeof(buf), LogmsgFormat, ##__VA_ARGS__); \
        Logger::getInstance().log(buf); \
    } while(0);

#define LOG_ERROR(LogmsgFormat, ...) \
    do \
    { \
        Logger::getInstance().setLogLever(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, sizeof(buf), LogmsgFormat, ##__VA_ARGS__); \
        Logger::getInstance().log(buf); \
    } while(0);

#define LOG_FATAL(LogmsgFormat, ...) \
    do \
    { \
        Logger::getInstance().setLogLever(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, sizeof(buf), LogmsgFormat, ##__VA_ARGS__); \
        Logger::getInstance().log(buf); \
        exit(-1); \
    } while(0);

#ifdef DEBUGOPEN
#define LOG_DEBUG(LogmsgFormat, ...) \
    do \
    { \
        Logger::getInstance().setLogLever(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, sizeof(buf), LogmsgFormat, ##__VA_ARGS__); \
        Logger::getInstance().log(buf); \
    } while(0);
#else
    #define LOG_DEBUG(LogmsgFormat, ...)
#endif

//定义日志级别
enum LogLever
{
    INFO,
    ERROR,
    FATAL,
    DEBUG,
};


/**
    日志类
*/
class Logger : public muduo::noncopyable
{
public:
    static Logger& getInstance();
    void setLogLever(int logLevel);
    void log(std::string msg);
private:
    int logLevel_;
    Logger(){}
};