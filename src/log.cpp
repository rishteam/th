#include <log.h>

namespace rl {

// static
Logger Logger::logger;

const char * Logger::LogName[LogLevel::LOG_LEVEL_NUM] = {
    "NONE", "INFO", "WARN", "DEBUG"
};

}