# Copyright (c) 2015, Simone Margaritelli <evilsocket at gmail dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#   * Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#   * Neither the name of ARM Inject nor the names of its contributors may be used
#     to endorse or promote products derived from this software without
#     specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
from pyadb.adb import ADB

try:
    adb = ADB()

    print "@ Pushing files to /data/local/tmp/tang/ ..."
    local_path = "libs\\armeabi-v7a\\"
    remote_path = "/data/local/tmp/tang/"

    adb.sh( "rm -rf /data/local/tmp/tang/injector /data/local/tmp/tang/libhook.so" )
    adb.push( local_path + "injector",  remote_path + "injector" )
    adb.push( local_path + "libhook.so", remote_path + "libhook.so" )
    adb.sh( "chmod 777 /data/local/tmp/tang/injector" )

    adb.clear_log()

    # get the pid to inject
    pid = input("pid: ");

    print "@ Injection into PID %d starting ..." % pid

    adb.sh( "/data/local/tmp/tang/injector %d /data/local/tmp/tang/libhook.so" % pid )
    adb.logcat("LIBHOOK")

except KeyboardInterrupt:
    print "\n\n@ CTRL+C detected, killing process ..."
    adb.pkill( process )
