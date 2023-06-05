#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<semaphore.h>
#include<sys/stat.h>

struct data{
	int a[5];
	sem_t empty, full, mutex;
	};
	
void main()
{	
	int i=0;
	int in = 0, out = 0;
	int shmid = shm_open("/buffer", O_CREAT|O_RDWR, 0777);
	ftruncate(shmid, sizeof(struct data));
	
	struct data* d = (struct data*)mmap(NULL, sizeof(struct data), PROT_WRITE|PROT_READ, MAP_SHARED, shmid, 0);
	sem_init(&(d->mutex),1,1);
	sem_init(&(d->empty),1,10);
	sem_init(&(d->full),1,0);
	
	while(1<5)
	{
		sem_getvalue(&(d->full),&i);
		
		if(i==0)
		{
			printf("\nBuffer Empty\n");
			while(i==0)
			{
				sem_getvalue(&(d->full),&i);
				
			}
		}
		else
		{
			int choice;
			printf("\nConsume an Item");
			scanf("%d", &choice);
			if(choice==1)
			{
				sem_wait(&(d->full));
				sem_wait(&(d->mutex));
				int consumed = d->a[in];
				d->a[in]=0;
				in = (in+1)%5;
				printf("\nItem Consumed : %d", consumed);
				sem_post(&(d->empty));
				sem_post(&(d->mutex));
			}
		}
	
	}
	
	
}
