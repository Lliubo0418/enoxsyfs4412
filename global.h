#ifndef __GLOBAL__H__
#define __GLOBAL__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <termios.h>
#include <syscall.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>


/*
    全局的线程函数声明
    全局的设备节点声明
    全局的消息队列传递的结构体信息声明
*/

#define MINITOR_NUM 1
#define QUEUE_MSG_LEN 32


/*设备定义*/
#define ZIGBEE_DEV "/dev/ttyUSB0"
#define GPRS_DEV   "/dev/ttyUSB1"
#define BEEPER_DEV "/dev/fsbeeper0"
#define LED_DEV    "/dev/fsled0"

/*全局结构体定义*/

/*ZigBee设备*/
struct zigbee_info{
    uint8_t flag[3];          //标识符，'m'--'s'--'m'  makeru--security--minitor
    uint8_t type;             //数据类型  'z'---zigbee 'a'---a9
    
    float temperature;        //温度
    float humidity;           //湿度
    float tempMax;
    float tempMin;
    float humidityMax;
    float humidityMin;

    uint32_t reserved[2];
};


/*A9设备*/
struct a9_info{
    uint8_t flag[3];
    uint8_t type;

    uint32_t adc;             //adc
    uint16_t gyrox;           //陀螺仪数据
    uint16_t gyroy;
    uint16_t gyroz;

    uint16_t accx;             //加速计数据
    uint16_t accy;
    uint16_t accz;     

    uint32_t reserved[2];

};

/*设备环境*/
struct dev_env_data{
    struct zigbee_info zigbee_info;
    struct a9_info     a9_info;
    uint32_t reserved[2];     //预留扩展其他平台设备
}

/*监控环境区域*/
struct env_info_home{
    struct dev_env_data minitor_no[MINITOR_NUM];
}

/*消息队列结构体*/
struct msg{
    long type;              //从消息队列接收消息时用于判断的消息类型
    long msgtype;           //具体的消息类型
    unsigned char text[QUEUE_MSG_LEN];    //消息内容
};






#endif