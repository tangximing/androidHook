/*
 * Copyright (c) 2015, Simone Margaritelli <evilsocket at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of ARM Inject nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
