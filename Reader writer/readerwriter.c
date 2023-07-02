#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define READER 3
#define WRITER 1
int shared_resource=0;
int read_count=0;
sem_t resource_mutex;
sem_t reader_mutex;
sem_t writer_mutex;

void *reader(void *arg)
{	int reader_id= *(int *)arg;
	while(1)
	{	sem_wait(&reader_mutex);
		read_count++;
		if(read_count==1)
		{	sem_wait(&resource_mutex);
		}
		sem_post(&reader_mutex);
		printf("Reader %d is reading\n", reader_id);
		sem_wait(&reader_mutex);
		read_count--;
		printf("Reader %d is finished\n", reader_id);
		if(read_count==0)
		{	sem_post(&resource_mutex);
		}
		sem_post(&reader_mutex);
		sleep(2);
	}
}

void *writer(void *arg)
{	int writer_id = *(int *)arg;
	while(1)
	{	printf("Writer %d has entered\n", writer_id);
		sem_wait(&writer_mutex);
		sem_wait(&resource_mutex);
		printf("Writer %d is writing\n", writer_id);
		shared_resource = writer_id;
		sleep(1);
		printf("Writer %d is finished\n", writer_id);
		sem_post(&resource_mutex);
		sem_post(&writer_mutex);
		sleep(2);
	}
}

void main()
{	int i;
	pthread_t readers[READER];
	pthread_t writers[WRITER];
	sem_init(&resource_mutex, 0, 1);
	sem_init(&reader_mutex, 0, 1);
	sem_init(&writer_mutex, 0, 1);
	for(int i=0; i<READER ;i++)
	{	int *reader_id=malloc(sizeof(*reader_id));
		*reader_id=i;
		pthread_create(&readers[i], NULL, reader, reader_id);
	}
	for(i=0; i<WRITER; i++)
	{	int *writer_id=malloc(sizeof(*writer_id));
		*writer_id=i;
		pthread_create(&writers[i], NULL, writer, writer_id);
	}
	for(i=0; i<READER; i++)
	{	pthread_join(readers[i], NULL);
	}
	for(i=0; i<WRITER; i++)
	{	pthread_join(writers[i], NULL);
	}
	sem_destroy(&resource_mutex);
	sem_destroy(&reader_mutex);
	sem_destroy(&writer_mutex);
}
