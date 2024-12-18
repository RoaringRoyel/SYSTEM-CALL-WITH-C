#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	pid_t p, p1;
	
	p = fork();
	
	if (p == 0){
	
		p1 = fork();
		
		if (p1 == 0){
		
			printf("I am grandchild\n");
		}
		
		else if (p1 > 0){
		
			wait(NULL);
			printf("I am child\n");
		}
		
		else{
		
			printf("Grandchild failed\n");
		
		}
	}
	
	else if (p > 0){
	
		wait(NULL);
		printf("I am parent\n");
	}
	
	else{
		printf("Child failed\n");
	}
	
	return 0;
}
