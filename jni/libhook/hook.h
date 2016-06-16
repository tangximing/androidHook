#ifndef HOOK_H
#define HOOK_H

#include <android/log.h>
#include <string>
#include <sys/types.h>
#include <dlfcn.h>
#include <unistd.h>
#include <vector>
#include <map>
#include "hooks/io.h"
#include "linker.h"

using namespace std;

#define HOOKLOG(F,...) \
    __android_log_print( ANDROID_LOG_DEBUG, "LIBHOOK", F, __VA_ARGS__ )

#define ORIGINAL( TYPENAME, ... ) \
    ((TYPENAME ## _t)find_original( #TYPENAME ))( __VA_ARGS__ )

#define DEFINEHOOK( RET_TYPE, NAME, ARGS ) \
    typedef RET_TYPE (* NAME ## _t)ARGS; \
    RET_TYPE hook_ ## NAME ARGS

#define ADDHOOK( SONAME, NAME ) \
    { #SONAME, #NAME, 0, (uintptr_t)&hook_ ## NAME }

typedef struct
{
    const char *soname;
    const char *name;
    uintptr_t   original;
    uintptr_t   hook;
}hook_t;

typedef struct ld_module
{
    uintptr_t   address;
    string name;

    ld_module( uintptr_t a, const string& n ) : address(a), name(n) {}
}ld_module_t;

typedef vector<ld_module_t> ld_modules_t;

ld_modules_t libhook_definehooks();
unsigned     libhook_addhook( const char *soname, const char *symbol, unsigned newval );

#endif
