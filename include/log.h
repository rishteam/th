#pragma once

#include <iostream>
#include <string>

#include <fmt/core.h>
#include <fmt/printf.h>

namespace rl {

// Singleton logger
// TODO: support multithreading

enum LogLevel: unsigned int
{
    LOG_NONE = 0,
    LOG_INFO,  // For info msg
    LOG_WARN,  // For Warning msg
    LOG_DEBUG, // For debug msg

    LOG_LEVEL_NUM // for count
};

#define LOG(level, format, ...) rl::Logger::logger.writeLog(level, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define INFO(format, ...) LOG(rl::LOG_INFO, format, ##__VA_ARGS__)
#define WARN(format, ...) LOG(rl::LOG_WARN, format, ##__VA_ARGS__)
#define DEBUG(format, ...) LOG(rl::LOG_DEBUG, format, ##__VA_ARGS__)

class Logger
{
public:
    static Logger logger;
    //

    static const char *LogName[LOG_LEVEL_NUM];

    void vwriteLog(LogLevel level, const char* file, const int line, const char * func, const char* format, fmt::format_args args)
    {
        fmt::printf("[%s] %s @ %s:%d\n", Logger::LogName[level], func, file, line);
        fmt::vprint(format, args);
        fmt::print("\n");
        fflush(stdout);
    }

    template<typename... Args>
    void writeLog(LogLevel level, const char* file, const int line, const char * func, const char* format, const Args & ... args)
    {
        vwriteLog(level, file, line, func, format, fmt::make_format_args(args...));
    }

private:
    Logger() = default;
};

}