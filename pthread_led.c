#include "global.h"

//led线程
void *pthread_led(void* arg){
    printf("pthread_led\n");

#if 0
1、打开设备节点
2、等待线程调度
3、获取控制命令
4、通过ioctl()控制led的亮灭
#endif
}