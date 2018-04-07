#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 100
#define BIG_NUMBER 1000000
void *print_prime_count(void *num) {
	
	long n = (long)num;
        printf("Prime calculation started for N=%ld!\n",n);
        int counter = 0;

        int checkprime(long n)
        {
            if (n == 1) return 0;
            else
            {
                for (long i = 2; i <= n / 2; i++)
                {
                    if (n % i == 0)
                    {
                        return 0;
                    }
                }
            }
 
            return 1;
        }
       
        for (long i = 2; i < n; i++)
        {
            int res = checkprime(i);
            if (res == 1) counter++;
        }
	
	printf ("Number of primes for N=%ld is %d\n",n,counter);
	pthread_exit(NULL);
}


int main() {

	pthread_t threads[NUM_THREADS];
	int  t = 0;
	int num;
	char input[BIG_NUMBER];
	fgets(input,BIG_NUMBER,stdin);
	while (input[0] != 'e' || input[1] != '\n') {
		
		char n [30];
		if (input[0] = 'p' && input[1] == ' ') {
			
			for (int  i = 0; input[i+2] != '\0' ; i++) {
				n[i] = input [i+2];
			}
			num = atoi(n); 
			

			int rc = pthread_create(&threads[t],NULL,print_prime_count,(void*)num);

			if(rc)
			{
			    printf("ERROR: pthread_create() return %d\n",rc);
			    exit(-1);
			}
			t++;
    		}

		else {
			printf("Supported commands:\n");
			printf("p N - Starts a new calculation for the number of primes from 1 to N\n");
			printf("e - Waits for all calculations to finish and exits\n");
		}
		fgets(input,BIG_NUMBER,stdin);
	}

	for(int i=0;i<t;i++)
	{
		int rc = pthread_join(threads[i],NULL);
		if(rc)
		{
			printf("ERROR: pthread_join() return %d\n",rc);
			exit(-1);
		}
	}
    pthread_exit(NULL);

    return 0;
}

