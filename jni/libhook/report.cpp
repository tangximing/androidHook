#include "report.h"
#include "hook.h"
#include <sstream>
#include <iomanip>
#include <time.h>

#define LOCK() pthread_mutex_lock(&__lock)
#define UNLOCK() pthread_mutex_unlock(&__lock)

static report_options_t __opts = { LOGCAT, "", 0 };
static pthread_mutex_t  __lock = PTHREAD_MUTEX_INITIALIZER;

long int timestamp() {
    struct timeval tp = {0};
    gettimeofday(&tp, NULL);

    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

static long int __started = timestamp();

void report_set_options( report_options_t *opts ) {
    LOCK();

    __opts.mode = opts->mode;
    __opts.dest = opts->dest;
    __opts.port = opts->port;

    UNLOCK();
}

std::ostringstream& parse( char fmt, std::ostringstream& s, va_list& va ) {
    switch( fmt )
    {
        case 'i':
            s << va_arg( va, int ) << " ";
        break;

        case 'u':
            s << va_arg( va, unsigned int ) << " ";
        break;

        case 'p':
            s << std::hex << std::setfill('0') << "0x" << va_arg( va, uintptr_t ) << " ";
        break;

        case 's':
            s << '"' << va_arg( va, const char * ) << '"' << " ";
        break;

        default:

            s << std::hex << std::setfill('0') << "0x" << va_arg( va, uintptr_t ) << " ";
    }

    return s;
}

void report_add( const char *fnname, const char *argsfmt, ... ) {
	va_list va;
    size_t i, argc = strlen(argsfmt);

    LOCK();

    if( __opts.mode == LOGCAT ) {
        std::ostringstream s;

        s << "[ ts=" << ( timestamp() - __started ) << " pid=" << getpid() << ", tid=" << gettid() << " ] " << fnname << "( ";

        va_start( va, argsfmt );

        for( i = 0; i < argc; ++i ) {
            char fmt = argsfmt[i];

            // next will be the return value, break
            if( fmt == '.' ){
                break;
            }

            s << va_arg( va, char * ) << "=";
            parse( fmt, s, va );
        }

        s << ")";

        // get return value
        if( i != argc ){
            char fmt = argsfmt[i + 1];
            s << " -> ";
            parse( fmt, s, va );
        }

        va_end( va );

        HOOKLOG( "%s", s.str().c_str() );
    }

    UNLOCK();
}
