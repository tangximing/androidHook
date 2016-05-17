ARM Inject
===
Reference: https://github.com/evilsocket/arminject

## How to Test

In order to test this, you'll need the Android NDK installed and a device connected to your USB port,
then simply run:

    1. ndk-build
    2. python test.py, input the process name to inject



    @ Pushing files to /data/local/tmp/tang ....
    @ Injection into PID 18233 starting ...

    I/LIBHOOK (18233): LIBRARY LOADED FROM PID 18233.
    I/LIBHOOK (18233): Found 104 loaded modules.
    I/LIBHOOK (18233): Installing 12 hooks.
    I/LIBHOOK (18233): [0xA0861000] Hooking /data/app/com.android.chrome-2/lib/arm/libchrome.so ...
    I/LIBHOOK (18233): [0xA0A68000] Hooking /data/app/com.android.chrome-2/lib/arm/libchrome.so ...
    I/LIBHOOK (18233): [0xAB8A9000] Hooking /system/vendor/lib/egl/libGLESv2_adreno.so ...
    I/LIBHOOK (18233): [0xAB9EC000] Hooking /system/vendor/lib/egl/libGLESv1_CM_adreno.so ...
    I/LIBHOOK (18233): [0xABA20000] Hooking /system/vendor/lib/libgsl.so ...
    I/LIBHOOK (18233):   open - 0xb6f31951 -> 0xa446577c
    I/LIBHOOK (18233):   write - 0xb6f55ec8 -> 0xa4464d5c
    I/LIBHOOK (18233):   read - 0xb6f56964 -> 0xa4464c70
    I/LIBHOOK (18233):   close - 0xb6f552e8 -> 0xa4464e54
    I/LIBHOOK (18233):   connect - 0xb6f30365 -> 0xa44657fc
    I/LIBHOOK (18233):   sendto - 0xb6f562a0 -> 0xa4465020
    I/LIBHOOK (18233):   recvfrom - 0xb6f5679c -> 0xa4465318
    I/LIBHOOK (18233):   shutdown - 0xb6f566ac -> 0xa4465518
    I/LIBHOOK (18233):   send - 0xb6f33851 -> 0xa4464f28
    I/LIBHOOK (18233):   recvmsg - 0xb6f560c0 -> 0xa446542c
    I/LIBHOOK (18233):   sendmsg - 0xb6f55de0 -> 0xa4465134
    ...
    ...
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 18
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 18
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] open('/data/data/com.android.chrome/shared_prefs/com.google.android.apps.chrome.omaha.xml', 0) -> 18
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 19
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 19
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] read( '/data/data/com.android.chrome/shared_prefs/com.google.android.apps.chrome.omaha.xml', 0xb007c00c, 16384 ) -> 655
    I/LIBHOOK (18233): [18233] close( '/data/data/com.android.chrome/shared_prefs/com.google.android.apps.chrome.omaha.xml' ) -> 0
    I/LIBHOOK (18233): [18233] write( 'pipe:[4020814]', W, 1, 2147483647 ) -> 1
    I/LIBHOOK (18233): [18233] write( '(14)', 18306, 5, -1601827487 ) -> 5
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 22
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 22
    I/LIBHOOK (18233): [18233] close( '/dev/ashmem' ) -> 0
    I/LIBHOOK (18233): [18233] close( '(22)' ) -> 0
    I/LIBHOOK (18233): [18233] read( '(18)', 0xa0860b6c, 16 ) -> 1
    I/LIBHOOK (18233): [18233] close( '(24)' ) -> 0
    I/LIBHOOK (18233): [18233] close( '(22)' ) -> 0
    I/LIBHOOK (18233): [18233] open('/dev/ashmem', 2) -> 22
    I/LIBHOOK (18233): [18233] recvfrom( 'socket:[4043146]', nysv, 2400, 64, 0x0, 0 ) -> 24
    I/LIBHOOK (18233): [18233] recvfrom( 'socket:[4043146]', nysv, 2400, 64, 0x0, 0 ) -> -1
    I/LIBHOOK (18233): [18233] read( '(18)', 0xa0860b6c, 16 ) -> 1
    I/LIBHOOK (18233): [18233] write( 'pipe:[4020814]', W, 1, 2147483647 ) -> 1
    I/LIBHOOK (18233): [18233] recvfrom( 'socket:[4043184]', , 2264, 64, 0x0, 0 ) -> -1
    I/LIBHOOK (18233): [18233] write( 'pipe:[4043980]', W, 1, -1 ) -> 1
    ...
    ...
    @ CTRL+C detected, killing process ...
