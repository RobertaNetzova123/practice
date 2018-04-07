#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>	
#define SIZE 20

int gold = 0;
pthread_mutex_t mutex;


void *dig(void* value)
{
	for(int k=0;k<20;k++)	
	{
		pthread_mutex_lock(&mutex);
		printf("Miner %d gathered 10 gold\n",(int)value);
		gold+=10;
		pthread_mutex_unlock(&mutex);
		
		sleep(2);
	
	}

	// pthread_exit(NULL);
	return NULL;
}

void *sell(void* value)
{
	for(int k=0;k<20;k++)	
	{	
			pthread_mutex_lock(&mutex);

			if(gold == 0 )
			{
				printf("The warehouse is empty,cannot sell!\n");
			} 
			else
			{
				
				printf("Trader %d sold 10 gold\n",(int)value);
				gold-= 10;
			}

			pthread_mutex_unlock(&mutex);
			sleep(2);
	}

	// pthread_exit(NULL);
	return NULL;
}

int main(int argc, char** argv) {
	
	int miner_num = 1;
	int trader_num = 1;

	if (argc > 1) {
		miner_num = atoi(argv[1]);
		trader_num = atoi(argv[2]);
	}

	pthread_t miners_threads[miner_num];
	pthread_t traders_threads[trader_num];

	pthread_mutex_init(&mutex, NULL);
	
	for (int i = 0; i < miner_num; ++i) {
		//printf("bne");
		pthread_create(&miners_threads[i], NULL, dig,(void*)i+1);

		
	}
	for (int i = 0; i < trader_num ; ++i) {
		pthread_create(&traders_threads[i], NULL, sell,(void*)i+1);
		
	
	}
	
	
	for (int i = 0; i < miner_num; ++i) {
		pthread_join(miners_threads[i],NULL);

		
	}
	for (int i = 0; i < trader_num ; ++i) {
		pthread_join(traders_threads[i],NULL);

	
	}
	
	printf("Gold: %d\n",gold);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}




