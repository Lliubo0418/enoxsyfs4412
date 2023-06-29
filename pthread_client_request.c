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

//������Ϣ������������߳�

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
					printf("��Щ������Ϊ��չ\n");
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
						sqlite_InsertLinknode (ENV_UPDATE, all_info_RT, sto_no, 0);//0,0分别昄1�7仓库号和货物种类叄1�7
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

		long msgtype;//�������Ϣ����
		��Ϣ���͵ķ��䣺
			1L: 		LED����
			2L:			����������
			3L:			��·LED��ģ��������
			4L:			����
			5L:			��ʪ����ֵ����
			6L-7L-8L-9L,���ڸ��˵���չ
			10L: 		3Gͨ��ģ��-GPRS 
		switch(msgbuf.msgtype){
			case 1L: ...  break;
			....
			default ....  break;
		}
#endif 