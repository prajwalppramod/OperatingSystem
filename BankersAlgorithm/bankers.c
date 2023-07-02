#include<stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
int need[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], allocation[MAX_PROCESSES][MAX_RESOURCES];
int isSafe(int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int nProcesses, int nResources)
{	int i,j;
	int work[MAX_RESOURCES];
	int finish[MAX_RESOURCES] = {0};
	for(int i=0; i<nResources; i++)
	{	work[i]=available[i];
	}
	for(int i=0; i<nProcesses; i++)
	{	for(int j=0; j<nResources; j++)
		{	need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	int count=0;
	int safeSequence[MAX_PROCESSES];
	while(count < nProcesses)
	{	int found=0;
		for(int i=0; i<nProcesses; i++)
		{	if(finish[i]==0)
			{	int j;
				for(j=0; j<nResources; j++)
				{	if( need[i][j] > work[j] || need[i][j]<0 )
					{	break;
					}
				}
				if(j==nResources)
				{	for(int j=0; j<nResources; j++)
					{	work[j]+=allocation[i][j];
					}
					safeSequence[count++]=i;
					finish[i]=1;
					found=1;
				}
			}
			
		}
		if(found==0)
		{	return 0;
		}
	}
	printf("\nSafe sequence is: ");
	for(int i=0; i<nProcesses; i++)
	{	printf("P%d, ", safeSequence[i]);
	}
	return 1;
}

void main()
{	
	int nProcesses, nResources, i ,j;
	printf("Enter number of processes: ");
	scanf("%d", &nProcesses);
	printf("Enter number of resources: ");
	scanf("%d", &nResources);
	printf("Enter available resource: ");
	for(i=0; i<nResources ; i++)
	{	scanf("%d", &available[i]);
	}
	printf("Enter maximum resource matrix\n");
	for(i=0; i<nProcesses; i++)
	{	for(j=0; j<nResources; j++)
		{	scanf("%d", &max[i][j]);
		}
	}
	printf("Enter allocated resource matrix\n");
	for(i=0; i<nProcesses; i++)
	{	for(j=0; j<nResources; j++)
		{	scanf("%d", &allocation[i][j]);
		}
	}
	int choice=0, request[MAX_RESOURCES], process_id, flag=0;
	do{	
		printf("Enter choice\n1.Safe Sequence\n2.Resource Request\n3.Exit\n");
		scanf("%d", &choice);
		switch(choice)
		{	case 1:
				if( isSafe(available, max, allocation, nProcesses, nResources))
				{	printf("\n----MAX-----\n");
					for(i=0; i<nProcesses; i++)
					{	for(j=0; j<nResources; j++)
						{	printf("%d  ", max[i][j]);
						}
						printf("\n");
					}
					printf("\n----ALLOCATION-----\n");
					for(i=0; i<nProcesses; i++)
					{	for(j=0; j<nResources; j++)
						{	printf("%d  ", allocation[i][j]);
						}
						printf("\n");
					}
					printf("\n----NEED-----\n");
					for(i=0; i<nProcesses; i++)
					{	for(j=0; j<nResources; j++)
						{	printf("%d  ", need[i][j]);
						}
						printf("\n");
					}
					printf("\nSystem is in safe state\n");
				}
				else
				{	printf("System is in unsafe state\n");
					break;
				}
			case 2:
				printf("Enter process resource request: ");
				for(int i=0; i<nResources; i++)
				{	scanf("%d", &request[i]);
				}
				printf("Enter process id: ");
				scanf("%d", &process_id);
				for(int i=0; i<nResources; i++)
				{	if( (request[i] > max[process_id][i] - allocation[process_id][i]) || (request[i] > available[i]))
					{	flag=1;
					}
				}
				if(flag==0)
				{	for(int j=0; j<nResources; j++)
					{	available[j] = available[j] - request[j];
						allocation[process_id][j] = allocation[process_id][j] + request[j];
						need[process_id][j] = need[process_id][j] - request[j];
					}
					if( isSafe(available, max, allocation, nProcesses, nResources))
					{	printf("\n----MAX-----\n");
						for(i=0; i<nProcesses; i++)
						{	for(j=0; j<nResources; j++)
							{	printf("%d  ", max[i][j]);
							}
							printf("\n");
						}
						printf("\n----ALLOCATION-----\n");
						for(i=0; i<nProcesses; i++)
						{	for(j=0; j<nResources; j++)
							{	printf("%d  ", allocation[i][j]);
							}
							printf("\n");
						}
						printf("\n----NEED-----\n");
						for(i=0; i<nProcesses; i++)
						{	for(j=0; j<nResources; j++)
							{	printf("%d  ", need[i][j]);
							}
							printf("\n");
					}
						printf("\nSystem is in safe state\n");
					}
					else
					{	printf("\nSystem is in unsafe state\n");
					}
				}
				else
				{	printf("Access not granted");
				}
		}
		
	
	}while(choice!=3);
	
}


















