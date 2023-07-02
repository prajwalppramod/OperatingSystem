#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
pthread_t philosopher[N];
sem_t chopstick[N];
sem_t mutex;
void *philosophers(void *arg)
{
    int i=*(int *)arg;
    while(1)
    {
        printf("\nPhilosopher %d is thinking\n", i);
        sleep(1);
        sem_wait(&mutex);
        sem_wait(&chopstick[LEFT]);
        sem_wait(&chopstick[RIGHT]);
        sem_post(&mutex);
        printf("Philosopher %d is eating\n", i);
        sleep(2);
        sem_post(&chopstick[RIGHT]);
        sem_post(&chopstick[LEFT]);
    }
}
int main()
{
    int i;
    for(i=0;i<N;i++)
    {
        sem_init(&chopstick[i],0,1);
    }
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
    {
        int *arg=malloc(sizeof(*arg));
        *arg=i;
        pthread_create(&philosopher[i],NULL,*philosophers,arg);
    }
    for(i=0;i<N;i++)
    {
        pthread_join(philosopher[i],NULL);
    }
    for(i=0;i<N;i++)
    {
        sem_destroy(&chopstick[i]);

    }
    sem_destroy(&mutex);
    return 0;
}