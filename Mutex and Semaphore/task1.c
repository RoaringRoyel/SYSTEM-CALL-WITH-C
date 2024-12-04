#include<pthread.h>
#include<stdio.h>
#include<string.h>
#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2
void * consumer(int *id); //thread = consumer
void * producer(int *id); // thread = producer

char buffer[BUFLEN];
char source[BUFLEN];
int pCount =0; //producer count
int cCount = 0; //consumer count
int buflen;


pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0,1}; //thread ids
int i =0;
int j =0;

int main(){
	pthread_t thread[NUMTHREAD];
	strcpy(source,"abcdef");
	buflen=strlen(source);
	//
	pthread_create(&thread[0],NULL,(void *)producer,&thread_id[0]);
	pthread_create(&thread[1],NULL,(void *)consumer,&thread_id[1]);
	
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	//
	return 0;
}

void * producer(int *id){
	while(pCount < MAX){
		pthread_mutex_lock(&count_mutex); //locking
		while( j >= BUFLEN){
			pthread_cond_wait(&full, &count_mutex);
		}
		buffer[j] = source[pCount % buflen]; //producing from source
		printf("%d produced %c by Thread %d\n",pCount,buffer[j],*(int*)id);
		pCount++; // 1 producer increased
		j++;
		
		pthread_mutex_unlock(&count_mutex); //unlocking
		pthread_cond_signal(&nonEmpty);
	}
	pthread_exit(NULL);
}



void * consumer(int *id){
	while(cCount < MAX){
		pthread_mutex_lock(&count_mutex); //locking
		while (j <=0){
			pthread_cond_wait(&nonEmpty, &count_mutex);
		}
		char a = buffer[j-1]; //using the buffer
		printf("%d consumed %c by Thread %d\n",cCount,a,*(int*)id);
		cCount++; // 1 decresing by consumer
		j--;
		pthread_mutex_unlock(&count_mutex); //unlocking
		pthread_cond_signal(&full);
	}
	pthread_exit(NULL);
}





















