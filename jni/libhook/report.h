#ifndef REPORT_H_
#define REPORT_H_

#include <android/log.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>

typedef enum {
    LOGCAT = 0
}
report_mode_t;

typedef struct {
    report_mode_t  mode;
    // for future use
    std::string    dest;
    unsigned short port;
}
report_options_t;

void report_set_options( report_options_t *opts );
void report_add( const char *fnname, const char *argsfmt, ... );

#endif
