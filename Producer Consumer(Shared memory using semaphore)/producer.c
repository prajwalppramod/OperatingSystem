#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<semaphore.h>
#include<sys/stat.h>

struct data
{	int items[10];
	sem_t mutex, empty, full;
};

void main()
{	int i=0, in=0, out=0;
	int shmid = shm_open("/buffer", O_CREAT|O_RDWR, 0777);
	ftruncate(shmid, sizeof(struct data));
	
	struct data *sharedmem = (struct data*)mmap(NULL, sizeof(struct data), PROT_WRITE|PROT_READ, MAP_SHARED, shmid, 0);
	sem_init(&(sharedmem->mutex), 1, 1);
	sem_init(&(sharedmem->empty), 1, 10);
	sem_init(&(sharedmem->full), 1, 0);
	
	if(sharedmem==MAP_FAILED)
	{	printf("Map creation failed\n");
	}
	
	while(1<5)
	{	
		sem_getvalue(&(sharedmem->full), &i);
		//printf("Size is = %d\n", i);
		if(i==10)
		{	printf("Buffer is full\n");
			while(i==10)
			{	sem_getvalue(&(sharedmem->full), &i);
			}
		}
		else
		{	int choice=0;
			printf("Enter 1 to start producing: ");
			scanf("%d", &choice);
			while(choice!=0)
			{	sem_getvalue(&(sharedmem->full), &i);
				sem_wait(&(sharedmem->empty));
				sem_wait(&(sharedmem->mutex));
				sharedmem->items[out]=choice;
				out=(out+1)%10;
				printf("Item produced\n");
				sem_post(&(sharedmem->full));
				sem_post(&(sharedmem->mutex));
			}
		}
	}
}
