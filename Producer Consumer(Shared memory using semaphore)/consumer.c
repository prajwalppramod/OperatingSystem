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
	{	sem_getvalue(&(sharedmem->full), &i);
		if(i==0)
		{	printf("Buffer empty...Waiting for producer...\n");
			while(i==0)
			{	sem_getvalue(&(sharedmem->full), &i);
			}
			
		}
		else
		{	int choice=1;
			printf("Consume an item? ");
			scanf("%d", &choice);
			while(choice==1)
			{	sem_wait(&(sharedmem->full));
				sem_wait(&(sharedmem->mutex));
				int consumed = sharedmem->items[in];
				sharedmem->items[in]=0;
				in=(in+1)%10;
				printf("Item consumed: %d\n", consumed);
				sem_post(&(sharedmem->empty));
				sem_post(&(sharedmem->mutex));
				
			}
		}
	}
}
