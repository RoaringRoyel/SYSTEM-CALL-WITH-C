#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

struct shared{
	char sel[100];
	int b;
};

int main(){
	struct shared user;
	int fd[2];
	int pipe_1 = pipe(fd);
	if (pipe_1 ==-1){
		perror("Pipe1");
	}
	
	printf("Provide Your Input From Fiven Options:\n");
	printf("1. Type a to Add Money\n");
	printf("2. Type w to Withdraw Money\n");
	printf("3. Type c to Check Balance\n");
	read(0,user.sel,sizeof(user.sel));
	write(fd[1],&user.sel,sizeof(user.sel));
	user.b = 1000;
	write(fd[1],&user.b,sizeof(int));
	printf("Your selection is %s\n",user.sel);
	
	pid_t opr;
	opr = fork();
	if(opr == -1){
		perror("Error in fork");
	}
	else if(opr == 0){
		read(fd[0],&user.sel,sizeof(user.sel));
		read(fd[0],&user.b,sizeof(int));
		close(fd[0]);
		//updating account
		if(*user.sel=='a'){
			printf("Enter amount to be added:\n");
			int money;
			scanf("%d",&money);
			if(money>=0){
				user.b= user.b + money;
				write(fd[1],&user.b,sizeof(int));
				printf("Balance Added successfully\n");
				printf("Updated balance after addition:\n%d\n",user.b);
			}
			else if(money<0){
				printf("Adding Failed, Invalid amount\n");
			}
		}
		else if(*user.sel=='w'){ //withdraw
			printf("Enter amount to be withdrawn:\n");
			int money;
			scanf("%d",&money);
			if(money>=0 && money <= user.b){
				user.b= user.b - money;
				write(fd[1],&user.b,sizeof(int));
				printf("Balance withdrawn successfully\n");
				printf("Updated balance after withdrawn:\n%d\n",user.b);
			}
			else{
				printf("Withdrawn Failed, Invalid amount\n");
			}
		
		}
		else if(*user.sel=='c'){
			printf("Your current balance is:\n%d\n",user.b);
		}
		else{
			printf("Invalid selection\n");
		}
		char temp[100]="Thank you for using";
		strcpy(user.sel,temp);
		write(fd[1],&user.sel,sizeof(user.sel));
		close(fd[1]);
		
	}
	else{
		wait();
		
		read(fd[0],&user.sel,sizeof(user.sel));
		printf("%s\n",user.sel);
		close(fd[0]);
		close(fd[1]);	
		
	}
	
	return 0;
}































