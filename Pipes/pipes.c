#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{	int fd1[2], fd2[2], fd3[2], n, i, sum=0;
	int pipe1message[10], pipe2message[10], pipe3message[10], readmessage[10];
	pid_t p;
	pid_t p2;
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	printf("Process 1: Getting Elements ");
	printf("\nEnter no of elements: ");
	scanf("%d", &n);
	printf("Enter the elements: ");
	for(i=0; i<n; i++)
	{	scanf("%d", &pipe1message[i]);
	}
	p=fork();
	if(p>0)
	{	close(fd1[0]);
		close(fd3[1]);
		printf("Writing to pipe1 ");
		write(fd1[1], pipe1message, sizeof(pipe1message));
		read(fd3[0], readmessage, sizeof(readmessage));
		printf("Sum of square of elements: ");
		printf("%d ", readmessage[0]);
	}
	
	else
	{	sleep(10);
		p2=fork();
		if(p2>0)
		{	close(fd1[1]);
			close(fd2[0]);
			read(fd1[0], readmessage, sizeof(readmessage));
			printf("Process 2: Reading from pipe 1 ");
			for(i=0; i<n; i++)
			{	printf("%d  ", readmessage[i]);
			}
			printf("Squaring elements  ");
			for(i=0; i<n; i++)
			{	pipe2message[i] = readmessage[i]*readmessage[i];
			}
			printf("Writing to pipe 2  ");
			write(fd2[1], pipe2message, sizeof(pipe2message));
		}
		else
		{	sleep(10);
			close(fd1[1]);
			close (fd3[0]);
			read(fd2[0], readmessage, sizeof(readmessage));
			printf("Process 2: Reading from pipe2. Message: ");
			for(i=0; i<n; i++)
			{	printf("%d  ", readmessage[i]);
			}
			for(i=0; i<n; i++)
			{	sum = sum + readmessage[i];
			}
			pipe3message[0]=sum;
			printf("Writing to pipe 3  ");
			write(fd3[1], pipe3message, sizeof(pipe3message));
			
		}
	}
}
