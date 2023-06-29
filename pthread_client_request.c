#include "global.h"

extern int msgid;
extern key_t key;

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

extern char recive_phone[12] ;
extern char center_phone[12] ;


struct msg msgbuf;

//处理消息队列里请求的线程

void* pthread_client_request(void *arg){
    if((key=ftok("/tmp",'g'))<0){
        perror("ftok failed\n");
        exit(-1);
    }

    msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
    if(msgid==-1){
        if(errno == EEXIST){
            msgid = msgget(key,0777);
        }else{
            perror("fail to msgget\n");
            exit(-1);
        }

    }
    printf("pthread_client_request\n");

    while(1){
        bzero(&msgbuf,sizeof(msgbuf));
        printf("wait from client request...\n");
        msgrcv(msgid,&msgbuf,sizeof(msgbuf)-sizeof(long),1L,0);
        printf("Get %ldL msg\n", msgbuf.msgtype);
        printf ("text[0] = %#x\n", msgbuf.text[0]);


        switch(msgbuf.msgtype){
            case 1L:
					printf("hello led\n");
				break;
			case 2L:
					printf("hello beep\n");
				break;
			case 3L:
					printf("hello seg\n");
				break;
			case 4L:
					printf("hello fan\n");
				break;
			
			case 5L:
					printf("set env data\n");
					printf("temMAX: %d\n",*((int *)&msgbuf.text[1]));
					printf("temMIN: %d\n",*((int *)&msgbuf.text[5]));
					printf("humMAX: %d\n",*((int *)&msgbuf.text[9]));
					printf("humMAX: %d\n",*((int *)&msgbuf.text[13]));
				break;                
			case 6L:
			case 7L:
			case 8L:
			case 9L:
					printf("这些可以作为扩展\n");
				break;

            case 10L:
				{
					int i = 0 , j = 0 ;
					for(i = 0 ; i < 11; i++){
						recive_phone[i] = msgbuf.text[i]; 	
					}
					recive_phone[i] = '\0';
					printf("recive:%s\n",recive_phone);
					for(j = 0 ;msgbuf.text[i] != '\0' && j < 12; i++, j++)
					{
						center_phone[j] =  msgbuf.text[i];
					}
					center_phone[j] = '\0';
					printf("center:%s\n",center_phone);

                    #if 0
						pthread_mutex_lock (&mutex_slinklist);
						sqlite_InsertLinknode (ENV_UPDATE, all_info_RT, sto_no, 0);//0,0鍒嗗埆鏄�浠撳簱鍙峰拰璐х墿绉嶇被鍙�
						pthread_mutex_unlock (&mutex_slinklist);
						pthread_cond_signal (&cond_sqlite);
                    #endif                   
 


                }         
                break;     
            default:

                break;  
        }
    }
}
#if 0

		long msgtype;//具体的消息类型
		消息类型的分配：
			1L: 		LED控制
			2L:			蜂鸣器控制
			3L:			四路LED灯模拟的数码管
			4L:			风扇
			5L:			温湿度最值设置
			6L-7L-8L-9L,用于个人的扩展
			10L: 		3G通信模块-GPRS 
		switch(msgbuf.msgtype){
			case 1L: ...  break;
			....
			default ....  break;
		}
#endif 