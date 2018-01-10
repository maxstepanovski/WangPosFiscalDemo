/*
* Android.mk //TODO:Here is makefile reference
* LOCAL_PATH:= $(call my-dir)

* include $(CLEAR_VARS)
* LOCAL_SRC_FILES:= pn547_iic_test_app.c

* LOCAL_MODULE:= pn547_app

* include $(BUILD_EXECUTABLE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <Android/log.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "pn544_i2c_driver.h"

#define SEND_CMD_NUM 2


int main() {
    const char* TAG = "pn548_i2c";
    const char* path = "/dev/fcdev";
    int ret = 0;
    int i = 0, j = 0;
    int num;
    int fp = 0;

    //NCI cmd
    unsigned char send_test_cmd[2][6] = {{0x04, 0x01, 0x00, 0x02, 0xee, 0xdb},
                                         {0x04, 0x01, 0x00, 0x30, 0xff, 0xcd}};
    unsigned char recv_resp[50] = {0};


    __android_log_print(ANDROID_LOG_DEBUG, TAG, "FC iic driver testing...");
    if ((ret = (fp = open(path, O_RDWR))) < 0) {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "FC open error retcode = %d, errno = %d\n, file path = %s", ret, errno, path);
        exit(0);
    }

    //hardware reset
    //ioctl(fp, PN544_SET_PWR, 1);
    //ioctl(fp, PN544_SET_PWR, 0);
    //ioctl(fp, PN544_SET_PWR, 1);

    for (num = 0; num < SEND_CMD_NUM; num++) {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "write command: ");
        for (i = 0; i < 6; i++) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "%.2x ", send_test_cmd[num][i]);
        }
        //Send cmd
        ret = write(fp, send_test_cmd[num], 6);
        if (ret < 0) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "FC write error, maybe in standby mode,  retcode = %d, errno = %d, retry...", ret, errno);
            //wait 50ms
        }

        usleep(50000);
        memset(recv_resp, 0, sizeof(recv_resp));

        if (num == 0) {
            j = 6;
        } else {
            j = 32;
        }

        ret = read(fp, &recv_resp[0], j);
        if (ret < 0) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "FC read error! retcode = %d, errno = %d", ret, errno);
            return errno;
        }
        //	j = strlen(recv_resp);
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "read responce j = %d: ");
        for (i = 0; i < j; i++) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "%.2X ", recv_resp[i]);
        }
    }
    close(fp);
    return 0;
}

