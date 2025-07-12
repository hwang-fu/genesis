#ifndef GENESIS_ASSERTF_H
#define GENESIS_ASSERTF_H

#include "generics.h"

typedef enum LogLevel LogLevel;
enum LogLevel {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

#define logger(level, ...)                                              \
        logger_(level, __FILE__, __LINE__, __VA_ARGS__)

#define info(...)                                                       \
        logger_(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)

#define warning(...)                                                    \
        logger_(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)

#define error(...)                                                      \
        logger_(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)


#define assertf(expr, ...)                                              \
        do {                                                            \
            if ( !(expr) )                                              \
                errorf_(__FILE__, __LINE__, __VA_ARGS__);               \
        } while (0)

#define cassert(expr)                                                   \
        do {                                                            \
            if (!(expr))                                                \
                errorf_(__FILE__, __LINE__, BOLD RED #expr ENDCRAYON ); \
        } while (0)

#define assert_eq(o1, o2)                                               \
        cassert(eq(o1, o2))

#define debug(...)                                                      \
        debug_(__FILE__, __LINE__, __VA_ARGS__)

#define TODO(...)                                                       \
        do {                                                            \
            errorf_(__FILE__, __LINE__, __VA_ARGS__);                   \
            exit(EXIT_FAILURE);                                         \
        } while (0)


void logger_(copy LogLevel level, borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);
void errorf_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);
void debug_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);

#endif // GENESIS_ASSERTF_H
