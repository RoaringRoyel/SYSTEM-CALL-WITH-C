#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>

struct msg{
	long int type;
	char txt[6];
};

int main(){
	
		
	char user[20];
	char cse[20]="cse321";
	printf("Please enter the workspace name\n");
	scanf("%s",user);
	if(strcmp(user,"cse321")==0){
		int snt;
		int msg_id;
		msg_id = msgget((key_t)11,0666|IPC_CREAT);
		
		if(msg_id == -1){
			perror("MSG_ID");
		}
		
		struct msg msg_1; //obj 1 for LOG IN 
		
		char temp[]="cse321";
		strcpy(msg_1.txt,temp);
		msg_1.type = 4;
		
		snt = msgsnd(msg_id,(void *)&msg_1,sizeof(msg_1.txt),0);
		if(snt == -1){
			perror("SNT FROM PARENT");
		}
		
		printf("Workspace name sent to otp generator from log inL %s\n",msg_1.txt);
		
		pid_t otp;
		otp = fork();//creating a OTP CHILD
		if(otp == -1){
			perror("OTP Fork");
		}
		
		if(otp == 0){
			
			struct msg otp_m; // recieving object
			
			if(msgrcv(msg_id,(void *)&otp_m,sizeof(otp_m.txt),4,IPC_NOWAIT)<0 ){//recieving txt from LOG IN
				perror("Reading in OTP");
			}
			printf("OTP generator received workspace name from log in: %s\n",otp_m.txt);
			
			struct msg msg_2; //obj 2
			msg_2.type = 3;
			int new_otp = getpid();
			char temp[20];
			snprintf(temp,sizeof(temp),"%d",new_otp);
			
			strcpy(msg_2.txt,temp);
			snt = msgsnd(msg_id,(void *)&msg_2,sizeof(msg_2.txt),0);//for LOG IN pro
			if(snt == -1){
				perror("SNT FROM OTP");
			}
			printf("OTP sent to log in from OTP generator: %s\n",msg_2.txt);
			
			
			struct msg msg_3; //onj 3
			msg_3.type = 2;
			strcpy(msg_3.txt,temp);
			snt = msgsnd(msg_id,(void *)&msg_3,sizeof(msg_3.txt),0); // for MAIL pro
			if(snt == -1){
				perror("SNT FROM OTP");
			}
			printf("OTP sent to mail from OTP generator: %s\n",msg_3.txt);
			
			pid_t mail;
			mail = fork();
			if(mail == -1){
				perror("FORK IN OTP");
			}
			else if(mail == 0){
				
				struct msg mail_m; //receiving object
				if(msgrcv(msg_id,(void *)&mail_m,sizeof(mail_m.txt),2,IPC_NOWAIT)<0 ){//from OTP to MAIL
					perror("Reading in OTP");
				}
				printf("Mail recieved OTP from  OTP generator: %s\n",mail_m.txt);
				
				struct msg msg_4;//obj 4
				msg_4.type = 1;
				strcpy(msg_4.txt,mail_m.txt);
				snt = msgsnd(msg_id,(void *)&msg_4,sizeof(msg_4.txt),0); // for LOG In from MAIL
				if(snt == -1){
					perror("SNT FROM OTP");
				}
				printf("OTP sent to log in from mail: %s\n",msg_4.txt);
			}
			else{
				wait(NULL);
			}
		}
		else{
			wait();
			struct msg log_otp,mail_otp;
			if(msgrcv(msg_id,(void *)&log_otp,sizeof(log_otp.txt),3,IPC_NOWAIT)<0 ){//from OTP to MAIL
					perror("Reading in OTP");
			}
			printf("Log in received OTP from OTP generator: %s\n",log_otp.txt);
			wait(1);
			
			if(msgrcv(msg_id,(void *)&mail_otp,sizeof(mail_otp.txt),1,IPC_NOWAIT)<0 ){//from OTP to MAIL
					perror("Reading in OTP");
			}
			printf("Log in received OTP from mail: %s\n",mail_otp.txt);
			wait(1);
			if(strcmp(log_otp.txt,mail_otp.txt)==0){
				printf("OTP Verified\n");
			}
			else{
				printf("OTP Incorrect\n");
				
			}
		msgctl(msg_id,IPC_RMID,NULL);
		}
	}
	else{
		printf("Invalid workspace name\n");
	}

	
	return 0;
}












