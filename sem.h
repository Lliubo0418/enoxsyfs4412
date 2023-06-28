#ifndef __SEM_H__
#define __SEM_H__


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int   val;
    struct semid_ds *buf;     //IPC_STAT,IPC_SET
    unsigned short *array;    //array for GETALL,SETALL
    struct seminfo *__buf;    //for IPC_INFO
};


/*函数定义写在.h文件中？这个文件只能被一个源文件包含？*/
int init_sem(int semid,int num,int val){
    union semun un;
    un.val = val;
    if(semctl(semid,num,SETVAL,un)<0){
        perror("semctl");
        exit(1);
    }
    return 0;
}

//p操作
int sem_p(int semid,int num){
    struct sembuf mybuf;
    mybuf.sem_flg = sem_undo;
    mybuf.sem_num = num;
    mybuf.sem_op =-1;
    if(semop(semid,&mubuf,1)<0){
        perror("semop");
        exit(1);
    }
    return 0;
}

//v操作 
int sem_v(int semid,int num){
    struct sembuf mybuf;
    mybuf.sem_flg = sem_undo;
    mybuf.sem_num = num;
    mybuf.sem_op =1;
    if(semop(semid,&mubuf,1)<0){
        perror("semop");
        exit(1);
    }
    return 0;
}


#endif
