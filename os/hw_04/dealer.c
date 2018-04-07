#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define SIZE 20

static pthread_mutex_t mutex[5];

void *deal (void* value) {
	
	for (int k = 0; k < 20;) {

		for(int i = 0; i < 5;i++) {

			if (pthread_mutex_trylock(&mutex[i]) == 0) {

				printf("Buyer %d takes car %d.\n",(int)value,i+1);
				sleep(1);
				printf("Buyer %d returns car %d.\n",(int)value,i+1);
				pthread_mutex_unlock(&mutex[i]);
				pthread_exit(NULL);
				k++;				
				break;
			}
		}
		
	}
}

int main(int argc, char** argv) {

	int dealer_num = 20;
	
	pthread_t dealers[dealer_num];

	for (int i = 0; i < 5; i++) {
		pthread_mutex_init(&mutex[i],NULL);
	}

	for  (int i =0; i < dealer_num; i++) {
		
		pthread_create(&dealers[i], NULL, deal,(void*)i+1);
	}

	for (int i = 0; i < dealer_num; ++i) {
		pthread_join(dealers[i],NULL);

		
	}

	for (int i = 0; i< 5; i++) {
		pthread_mutex_destroy(&mutex[i]);
	}
	return 0;
}
