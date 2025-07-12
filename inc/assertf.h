#ifndef GENESIS_ASSERTF_H
#define GENESIS_ASSERTF_H

#include "crayon.h"
#include "generics.h"

// Log level enumeration used to categorize logging messages.
typedef enum LogLevel LogLevel;
enum LogLevel {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

#define logging(level, ...)                                              \
        logging_(level, __FILE__, __LINE__, __VA_ARGS__)

#define info(...)                                                       \
        logging_(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)

#define warning(...)                                                    \
        logging_(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)

#define error(...)                                                      \
        logging_(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)


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

#define abort(...)                                                      \
        errorf_(__FILE__, __LINE__, __VA_ARGS__)

#define debug(...)                                                      \
        debug_(__FILE__, __LINE__, __VA_ARGS__)

#define TODO(...)                                                       \
        do {                                                            \
            errorf_(__FILE__, __LINE__, __VA_ARGS__);                   \
            exit(EXIT_FAILURE);                                         \
        } while (0)

#define SHUTDOWN                                                        \
        exit(EXIT_FAILURE)

/**
 * scp(ptr):
 *      1. Asserts that `ptr` is not null.
 */
#define scp(ptr)                                                        \
        assertf(ptr != nil, BOLD " nil " ENDCRAYON "pointer at" ITALIC " %s()" ENDCRAYON, __FUNCTION__)


/**
 * @brief Logger Constructor.
 */
void logger_ctor();

/**
 * @brief Logger Destructor.
 */
void logger_dtor();

/**
 * @brief Internal function to log messages with formatting.
 *
 * @param level     LogLevel enumeration.
 * @param filename  Source file where the log is issued.
 * @param line      Line number in the source file.
 * @param fmt       printf-style format string.
 */
void logging_(copy LogLevel level, borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);

/**
 * @brief Internal function to log an error message and optionally terminate.
 *
 * @param filename  Source file where the error occurred.
 * @param line      Line number.
 * @param fmt       printf-style format string.
 */
void errorf_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);

/**
 * @brief Internal function to log debug information.
 *
 * @param filename  Source file where debug is logged
 * @param line      Line number
 * @param fmt       printf-style format string
 */
void debug_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...);

#endif // GENESIS_ASSERTF_H
