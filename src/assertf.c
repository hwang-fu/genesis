#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "crayon.h"
#include "shared.h"
#include "assertf.h"
#include "utility.h"
#include "generics.h"

owned           char * logfile = nil;

borrowed static FILE * logger  = nil;

void logger_ctor() {
    if (logger) {
        return;
    }

    if (logfile) {
        logger = fopen(logfile, "w");
    }
    else {
        logger = fopen("log.txt", "w");
    }
    scp(logger);
}

void logger_dtor() {
    scp(logger);
    copy int ret = fclose(logger);
    if (logfile) {
        assertf(eq(0, ret), "failed to close file [%s]!", logfile);
        sfree(logfile);
    }
    else {
        assertf(eq(0, ret), "failed to close file [log.txt]!");
    }
}

void logging_(copy LogLevel level, borrowed const char * filename, copy const int line, borrowed const char * fmt, ...) {
    scp(logger);
    switch (level) {
        case LOG_INFO:
        {
            fprintf(logger, "[INFO]\n");
            fprintf(logger, "%s\n", s_localtime());
            fprintf(logger, "@[%s]:[%d]\n", filename, line);
            va_list args;
            va_start(args, fmt);
            vfprintf(logger, fmt, args);
            va_end(args);
            fprintf(logger, LF);
            fprintf(logger, LF);
        } break;

        case LOG_WARNING:
        {
            fprintf(logger, "[WARNING]\n");
            fprintf(logger, "%s\n", s_localtime());
            fprintf(logger, "@[%s]:[%d]\n", filename, line);
            va_list args;
            va_start(args, fmt);
            vfprintf(logger, fmt, args);
            va_end(args);
            fprintf(logger, LF);
            fprintf(logger, LF);
        } break;

        case LOG_ERROR:
        {
            fprintf(logger, "[ERROR]\n");
            fprintf(logger, "%s\n", s_localtime());
            fprintf(logger, "@[%s]:[%d]\n", filename, line);
            va_list args;
            va_start(args, fmt);
            vfprintf(logger, fmt, args);
            va_end(args);
            fprintf(logger, LF);
            fprintf(logger, LF);

            errorf_(filename, line, "critical error - seeing logging in %s", (logfile) ? logfile : "log.txt");
        } break;

        default:
        {
        } break;
    }
}

void errorf_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...) {
    fprintf(
        stderr, 
        BOLD RED "\t[ERROR]\n" ENDCRAYON
    );
    fprintf(
        stderr, 
        UNDERLINE "\t%s\n" ENDCRAYON,
        s_localtime()
    );
    fprintf(
        stderr, 
        UNDERLINE "\t@[%s]:[%d]\n" ENDCRAYON,
        filename, line
    );

    fprintf(stderr, BOLD);

    va_list args;
    va_start(args, fmt);
    fprintf(stderr, TAB);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, LF);
    va_end(args);

    fprintf(stderr, ENDCRAYON);

    exit(EXIT_FAILURE);
}

void debug_(borrowed const char * filename, copy const int line, borrowed const char * fmt, ...) {
    fprintf(
        stderr, 
        BOLD BLUE "\t[DEBUG]\n" ENDCRAYON
    );
    fprintf(
        stderr, 
        UNDERLINE "\t%s\n" ENDCRAYON,
        s_localtime()
    );
    fprintf(
        stderr, 
        UNDERLINE "\t@[%s]:[%d]\n" ENDCRAYON,
        filename, line
    );

    fprintf(stderr, BOLD);

    va_list args;
    va_start(args, fmt);
    fprintf(stderr, TAB);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, LF);
    va_end(args);

    fprintf(stderr, ENDCRAYON);
}

