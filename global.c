#include "global.h"


pthread_mutex_t mutex_client_request,
                mutex_buzzer,
                mutex_led,
                mutex_refresh,
                mutex_zigbee,
                mutex_sms,
                mutex_sqlite;

pthread_cond_t  cond_client_request,
                cond_buzzer,
                cond_led,
                cond_refresh,
                cond_sms,
                cond_sqlite,
                cond_zigbee;

int msgid;
int shmid;             //共享内存
int semid;             //信号量

key_t msg_key;            
key_t shm_key;
key_t sem_key;


char recive_phone[12] =  {0};
char center_phone[12] =  {0};


struct env_info_home home_all_env_info;

int send_msg_queue(long type,unsigned char text){
    struct msg msgbuf;
    msgbuf.type=1;
    msgbuf.msgtype=type;
    msgbuf.text[0]=text;

    if(msgsnd(msgid,&msgbuf,(sizeof(msgbuf)-sizeof(long),0)== -1){
        perror("fail to msgsnd");
        exit(1);
    }
    return 0;
}