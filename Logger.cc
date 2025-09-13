#include "Logger.h"

#include <iostream>

#include "Timestamp.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::setLogLever(int logLevel)
{
    logLevel_ = logLevel;
}

void Logger::log(std::string msg)
{
    switch (logLevel_)
    {
        case INFO:
            std::cout << "[INFO] ";
            break;
        case ERROR:
            std::cout << "[ERROR] ";
            break;
        case FATAL:
            std::cout << "[FATAL] ";
            break;
        case DEBUG:
            std::cout << "[DEBUG] ";
            break;
        default:
            break;
    }

    std::cout << "Time: " << Timestamp::now().toString() << " " << msg << std::endl;
}