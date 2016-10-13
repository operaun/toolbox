#!/usr/bin/env python

import os

print "--| installing ccache package and configuration"
# TODO(jongmin): Check permission. (is root required?)

os.system("pkg install ccache")

with open("/etc/make.conf", 'a') as make_file:
    make_file.write('''
.if (!empty(.CURDIR:M/usr/src*) || !empty(.CURDIR:M/usr/obj*))
        .if !defined(NOCCACHE) && exists(/usr/local/libexec/ccache/world/cc)
                CC:=\${CC:C,^cc,/usr/local/libexec/ccache/world/cc,1}
                CXX:=\${CXX:C,^c\+\+,/usr/local/libexec/ccache/world/c++,1}
        .endif
.endif
    ''')

# comment(jongmin): Which profile should we use, $HOME? or /root?
# TODO(jongmin): Check if there already exist CCACHE config in profile
#with open("~/.profile", 'a') as profile_file:
with open("/root/.profile", 'a') as profile_file:
    profile_file.write('''
export PATH=/usr/local/libexec/ccache:$PATH
export CCACHE_PATH=/usr/bin:/usr/local/bin
export CCACHE_DIR=/var/tmp/ccache
export CCACHE_LOGFILE=/var/log/ccache.log
    ''')

os.system("ccache --set-config=max_size=10G")

print "--> ccache installation and configuration done\n PLEASE DO 'source ~/.profile' to apply PATH"
