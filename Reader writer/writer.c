#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t mutex,r_mutex;
int rCount=0;
pthread_t readers[3],writers[1];
int readerId[3],writerId[1];

void *reader(void *args)
{
 int reader_id=*((int *)args);
 while(1)
 {
  int i=1;
  
  while(i!=0)
  {
   sem_getvalue(&r_mutex,&i);
   sem_wait(&mutex);
   rCount++;
   printf("\nReader %d has entered..ReadCount=%d",reader_id,rCount);
   if(rCount==1)
   {
    sem_wait(&r_mutex);
   }
   sem_post(&mutex);
   sleep(2);
   sem_wait(&mutex);
   rCount--;
   if(rCount==0)
    sem_post(&r_mutex);
   printf("\nReader %d has exited..ReadCount=%d",reader_id,rCount);
   sem_post(&mutex);
   sleep(2);
  }
 }
}
void *writer(void *args)
{
    int writer_id=*((int *)args);
    while(1)
    {
        int i;
        sem_getvalue(&mutex,&i);
        if(i!=0)
        {
            sem_wait(&r_mutex);
            printf("\nWriter %d has entered",writer_id);
            sem_post(&r_mutex);
            printf("\nWriter %d has exited",writer_id);  
            sleep(1);
        }
    }
}
void main()
{
    sem_init(&mutex,0,1);
    sem_init(&r_mutex,0,1);

    for(int i=0;i<3;i++)
    {
        writerId[i]=i;
        readerId[i]=i;
        pthread_create(&readers[i],NULL,reader,&readerId[i]);

    }
    for(int i=0;i<1;i++)
    {
        pthread_create(&writers[i],NULL,writer,&writerId[i]);
    }

    for(int i=0;i<3;i++)
        pthread_join(readers[i],NULL); 
    for(int i=0;i<1;i++)
    pthread_join(writers[i],NULL);
}