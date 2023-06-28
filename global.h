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
    ȫ�ֵ��̺߳�������
    ȫ�ֵ��豸�ڵ�����
    ȫ�ֵ���Ϣ���д��ݵĽṹ����Ϣ����
*/

#define MINITOR_NUM 1
#define QUEUE_MSG_LEN 32


/*�豸����*/
#define ZIGBEE_DEV "/dev/ttyUSB0"
#define GPRS_DEV   "/dev/ttyUSB1"
#define BEEPER_DEV "/dev/fsbeeper0"
#define LED_DEV    "/dev/fsled0"

/*ȫ�ֽṹ�嶨��*/

/*ZigBee�豸*/
struct zigbee_info{
    uint8_t flag[3];          //��ʶ����'m'--'s'--'m'  makeru--security--minitor
    uint8_t type;             //��������  'z'---zigbee 'a'---a9
    
    float temperature;        //�¶�
    float humidity;           //ʪ��
    float tempMax;
    float tempMin;
    float humidityMax;
    float humidityMin;

    uint32_t reserved[2];
};


/*A9�豸*/
struct a9_info{
    uint8_t flag[3];
    uint8_t type;

    uint32_t adc;             //adc
    uint16_t gyrox;           //����������
    uint16_t gyroy;
    uint16_t gyroz;

    uint16_t accx;             //���ټ�����
    uint16_t accy;
    uint16_t accz;     

    uint32_t reserved[2];

};

/*�豸����*/
struct dev_env_data{
    struct zigbee_info zigbee_info;
    struct a9_info     a9_info;
    uint32_t reserved[2];     //Ԥ����չ����ƽ̨�豸
}

/*��ػ�������*/
struct env_info_home{
    struct dev_env_data minitor_no[MINITOR_NUM];
}

/*��Ϣ���нṹ��*/
struct msg{
    long type;              //����Ϣ���н�����Ϣʱ�����жϵ���Ϣ����
    long msgtype;           //�������Ϣ����
    unsigned char text[QUEUE_MSG_LEN];    //��Ϣ����
};






#endif