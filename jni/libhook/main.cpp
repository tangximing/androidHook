#include "hook.h"
#include "hooks/io.h"

static hook_t __hooks[] = {
    ADDHOOK( /system/lib/libjavacore.so, open ),
    ADDHOOK( /system/lib/libjavacore.so, connect ),
    ADDHOOK( /system/lib/libbinder.so, ioctl)
};

#define NHOOKS ( sizeof(__hooks) / sizeof(__hooks[0] ) )

uintptr_t find_original( const char *name ) {
    for( size_t i = 0; i < NHOOKS; ++i ) {
        if( strcmp( __hooks[i].name, name ) == 0 ){
            return __hooks[i].original;
        }
    }

    HOOKLOG( "[%d] !!! COULD NOT FIND ORIGINAL POINTER OF FUNCTION '%s' !!!", getpid(), name );

    return 0;
}

void __attribute__ ((constructor)) libhook_main()
{
    HOOKLOG( "In the Libhook.so: \nLIBRARY LOADED FROM PID %d.", getpid() );

    for( size_t i = 0; i < NHOOKS; ++i ) {
        unsigned tmp = libhook_addhook( __hooks[i].soname, __hooks[i].name, __hooks[i].hook );
        if( __hooks[i].original == 0 && tmp != 0 ){
            __hooks[i].original = (uintptr_t)tmp;

            HOOKLOG( " %s : %s - 0x%x -> 0x%x", __hooks[i].soname, __hooks[i].name, __hooks[i].original, __hooks[i].hook );
        }
    }
}
