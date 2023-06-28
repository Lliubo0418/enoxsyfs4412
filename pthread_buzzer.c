#include "global.h"

//A9蜂鸣器线程

void *pthread_buzzer(void *arg){
    printf("pthread_buzzer\n");

#if 0
1、开启设备
2、线程条件等待
3、获取控制标志
4、通过ioctl()来控制buzzer

#endif
}