#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	FILE *file_prompt;
	char file_name[100];
	char string[9999];
	
	if (argc != 2){
		printf("Use: %s <filename>\n", argv[0]);
		return 1;
	}
	
	strcpy(file_name, argv[1]);
	
	if (access(file_name, F_OK) == -1){
		printf("File dose not exist. Creating file name: %s\n", file_name);
		file_prompt = fopen(file_name, "w");
	}
	else{	
		file_prompt = fopen(file_name, "a");
	}
	
	printf("Enter strings:\n");
	printf("If you want to stop writing then write -1\n");
	
	while(1){
		scanf("%s", string);
		int temp = strcmp(string, "-1");
		
		if (temp == 0){
			break;
		}
		
		fprintf(file_prompt, "%s\n", string);
	}
	
	fclose(file_prompt);
	
	return 0;
}
