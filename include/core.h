#pragma once

#include <log.h>

#ifdef RL_DEBUG
    #define RL_ENABLE_ASSERT
#endif

// TODO: implment other platform's debugbreak

#ifdef RL_ENABLE_ASSERT
#define RL_ASSERT(x, fmt, ...)                                 \
    {                                                          \
        if (!(x))                                              \
        {                                                      \
            RL_ERROR("Assertion Failed: " fmt, ##__VA_ARGS__); \
            __builtin_debugtrap();                             \
        }                                                      \
    }
#else
#define RL_ASSERT(x, fmt, ...)
#endif
