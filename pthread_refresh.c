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
    struct env_info_home home_all_env_info;
};

struct shm_addr *shm_buf;

int file_env_info_struct(struct  env_info_home *rt_status,int home_id);


//刷新线程
void *pthread_refresh(void *arg){
    //临界匄1�7 信号釄1�7
    if((sem_key =ftok("/tmp",'i'))<0){
        perror("ftok failed \n");
        exit(-1);
    }

    semid =semget(sem_key,1,IPC_CREAT|IPC_EXCL|0666);
    if(semid == -1){
        if(errno == EEXIST){
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

    shmid = shmget(shm_key,N,IPC_CREAT|IPC_EXCL|0666);
    if(shmid == -1){
        if(errno ==EEXIST){
            shmid = shmmmget (key,N,0777);
        }else(
            perror("failed to shmget\n");
            exit(1);
        )

    }

    //share memap
    if((shm_buf = (struct shm_addr *)shmat(shmid,NULL,0))== (void *)-1){
        perror("fail to shmat");
        exit(1);
    }

    printf("pthread_refresh ......>>>>>>\n");

#if 0
    bzero(shm_buf,sizeof(struct shm_addr));
    while(1){
        sem_p(semid,0);
        shm_buf->shm_status =1 ;
        file_env_info_struct(&shm_buf->home_all_env_info,shm_buf->shm_status);
        sleep(1);
        sem_v(semid,0);
    }
    

#endif


}

int file_env_info_struct(struct env_info_home * rt_status,int home_id){
    int env_info_size =sizeof(struct env_client_home);
    printf("env_info_size = %d\n",env_info_size);

    rt_status->minitor_no[home_id].a9_info.adc =9.0;
    rt_status->minitor_no[home_id].a9_info.accx= -14.0;
    rt_status->minitor_no[home_id].a9_info.accy=20.0;
    rt_status->minitor_no[home_id].a9_info.accz=40.0;
    rt_status->minitor_no[home_id].a9_info.gyrox=500.0;
    rt_status->minitor_no[home_id].a9_info.gyroy=520.0;
    rt_status->minitor_no[home_id].a9_info.gyroz=34.0;
    rt_status->minitor_no[home_id].a9_info.reserved[0]= 1.01;



    rt_status->minitor_no[home_id].zigbee_info.temperature=20.0;
    rt_status->minitor_no[home_id].zigbee_info.tempMax=30.0;
    rt_status->minitor_no[home_id].zigbee_info.tempMin=1.0;
    rt_status->minitor_no[home_id].zigbee_info.humidity=40.0;
    rt_status->minitor_no[home_id].zigbee_info.humidityMax=75.0;
    rt_status->minitor_no[home_id].zigbee_info.humidityMin=10.0;

    return 0;
}