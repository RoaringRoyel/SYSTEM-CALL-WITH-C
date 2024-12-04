#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

#define MaxCrops 5
#define warehouseSize 5

sem_t empty;
sem_t full;
int in =0;
int out =0;

char crops[warehouseSize]={'R','W','p','S','M'};
char warehouse[warehouseSize] = {'N','N','N','N','N'};

pthread_mutex_t mutex;

void * Farmer(void *far){ //producer
	for(int i=0;i<MaxCrops;i++){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex); //lock
		warehouse[in] = crops[*(int *)far];
		printf("Farmer %d:Insert crops %c at %d\n",*(int *)far,warehouse[in],in);
		in=(in + 1 )%warehouseSize;
		
		pthread_mutex_unlock(&mutex); // unlock
		sem_post(&full);
	}
	printf("Farmer: %d",*(int *)far);
	for(int i=0;i<warehouseSize;i++){
		printf("%c",warehouse[i]);
	}
	printf("\n");
	pthread_exit(NULL);
}
void * ShopOwner(void *sho){
	for(int i=0;i<MaxCrops;i++){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex); //lock
		warehouse[out] = warehouse[*(int *)sho];
		printf("Shop Owner %d:Removed crops %c from %d\n",*(int *)sho,warehouse[out],out);
		out=(out + 1)%warehouseSize;
		
		pthread_mutex_unlock(&mutex); // unlock
		sem_post(&full);
	}
	printf("Shop Owner: %d",*(int *)sho);
	for(int i=0;i<warehouseSize;i++){
		printf("%c",warehouse[i]);
	}
	printf("\n");
	pthread_exit(NULL);
}


int main(){
	pthread_t Far[5],Sho[5];
	pthread_mutex_init(&mutex,NULL);
	sem_init(&empty,0,warehouseSize);
	sem_init(&full,0,0);
	
	int a[5] = {1,2,3,4,5};
	
	for(int i=0;i<5;i++){
		pthread_create(&Far[i],NULL,(void *)Farmer,(void *)&a[i]);
	}
	for(int i=0;i<5;i++){
		pthread_create(&Sho[i],NULL,(void *)ShopOwner,(void *)&a[i]);
	}
	for(int i=0;i<5;i++){
		pthread_join(Far[i],NULL);
	}
	for(int i=0;i<5;i++){
		pthread_join(Sho[i],NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}

















