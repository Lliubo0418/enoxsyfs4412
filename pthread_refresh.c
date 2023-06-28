#include "global.h"
#include "sem.h"


#define N 1024

extern msgid;
extern shmid;
extern semid;

extern key_t msg_key;            
extern key_t shm_key;
extern key_t sem_key;

extern struct env_info_home home_all_env_info;


struct shm_addr{
    char shm_status;          //用来区分共享内存数据              
    truct env_info_home home_all_env_info;
};

struct shm_addr *shm_buf;

int file_env_info_struct(struct  env_info_home *rt_status,int home_id);


//刷新线程
void *pthread_refresh(void *arg){
    //临界区 信号量
    if((sem_key =ftok("/tmp",'i'))<0){
        perror("ftok failed \n");
        exit(-1);
    }

    semid =semget(sem_key,1,IPC_CREAT|IPC_EXCL|0666);
    if(semid == -1){
        if(errot == EEXIST){
            semid= semget(sem_key,1,0777);
        }else{
            perror("failed to semget\n");
            exit(1);
        }
    }
    else{
        init_sem(semid,0,1);
    }

    //共享内存
    if((shm_key = ftok("/tmp",'i'))<0){
        perror("ftok failed\n");
        exit(-1);
    }

    

}