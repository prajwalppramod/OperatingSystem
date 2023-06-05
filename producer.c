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
		sem_getvalue(&(d->full), &i);
		printf("\nSize = %d\n",i);
		if(i==5)
		{
			printf("Buffer Full\n");
			while(i == 5)
			{	
				sem_getvalue(&(d->full),&i);
				
			}
		
			
		}
		else
		{
			printf("Enter an item to produce ");
			int choice;
			scanf("%d", &choice);
			if(choice!=0)
			{
				sem_getvalue(&(d->full),&i);
				sem_wait(&(d->empty));
				sem_wait(&(d->mutex));
				d->a[out]=choice;
				out = (out+1)%5;
				printf("Item Produced..\n");
				sem_post(&(d->full));
				sem_post(&(d->mutex));
			}
			
		}
	}


}
