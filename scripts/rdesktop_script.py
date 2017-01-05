#!/usr/bin/python
import os 
import sys; sys.dont_write_bytecode = True

if __name__ == '__main__':
    sys.exit(
        os.system(
            "rdesktop YOUR_REMOTE_ADDRESS -g 1920x1080 -u \
             YOUR_REMOTE_USER_NAME -p YOUR_REMOTE_PASSWORD -k ko -fP"))

#rdesktop YOUR_REMOTE_ADDRESS -g 1920x1080 -u Naver -k ko -g 100% -PKD
