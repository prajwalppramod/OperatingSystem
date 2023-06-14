#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>


int n = 5;
int state[5] = {1,1,1,1,1};
int phil[5] = {0,1,2,3,4};
sem_t S[5];
int LEFT = 1;
int RIGHT = 1;



void take_fork(int phnum)
{
	sem_getvalue(&(S[phnum]),&LEFT);
	//printf("\nTake_LEFT = %d",LEFT);
	sem_getvalue(&(S[(phnum+1)%n]),&RIGHT);
	//printf("\nTake_RIGHT = %d",RIGHT);
	if(state[phnum] == 1 && LEFT == 1  && RIGHT == 1)
	{
		state[phnum] = 0;
		sem_wait(&S[phnum]);
		sem_wait(&S[(phnum+1)%n]);
		//printf("\nPhilosopher %d takes fork %d and %d \n", phnum+1, phnum, ((phnum+1)%n));
		printf("Philosopher %d is Eating\n", phnum+1);
	}

}

void put_fork(int phnum)
{
	if(state[phnum] == 0 && LEFT == 0  && RIGHT == 0)
	{
        sem_getvalue(&(S[phnum]),&LEFT);
        //printf("\nput_LEFT = %d",LEFT);
        sem_getvalue(&(S[(phnum+1)%n]),&RIGHT);
        //printf("\nput_RIGHT = %d",RIGHT);
        //printf("\nPhilospher %d putting fork %d and %d down\n",phnum+1, phnum, ((phnum+1)%n));
        printf("Philosopher %d is thinking\n", phnum+1);
        sem_post(&S[phnum]);
        sem_post(&S[(phnum+1)%n]);
        state[phnum] = 1;
	}

}

void *philosopher(void *num)
{
	while(1)
	{
		int *i = num;
		sleep(1);
		take_fork(*i);
		sleep(1);
		put_fork(*i);
	}
} 

int main()
{
	int i;
	pthread_t thread_id[n];
	
	for(i=0; i<n; i++)
	{
		sem_init(&S[i],0, 1);
	}
	
	for(i=0; i<n; i++)
	{
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
		printf("Philosopher %d is thinking\n", i+1);
	}
	for(i=0; i<n; i++)
	{
		pthread_join(thread_id[i],NULL);
	}
	
}
