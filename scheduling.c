#include<stdio.h>
#include<stdlib.h>

int slice;
int n,choice,processed;
float totalWT,totalTAT,time;
float avg_WT,avg_TAT;

struct process
{
	int pid;
	int AT;
	int BT;
	int prio;
	int WT;
	int TAT;
	int CT;
	int flag;
	int flag1;
	int RT;
};

void sort(struct process p[])
{
	struct process temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(p[j].AT>p[j+1].AT)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
}

void display(struct process p[])
{
	printf("\n\tP_ID\tAT\tBT\tWT\tTAT\tCT\n");
	printf("--------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
	{
		printf("\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].AT,p[i].BT,p[i].WT,p[i].TAT,p[i].CT);
	}
}

void FCFS(struct process p[])
{
	totalWT=0;
	totalTAT=0;
	time =0;
	
	
	
	for(int i=0;i<n;i++)
	{
		if(time<p[i].AT)
		{
			time=p[i].AT;
		}
		p[i].WT=time-p[i].AT;
		p[i].TAT=p[i].WT+p[i].BT;
		time+=p[i].BT;
		p[i].CT=time;
		totalWT+=p[i].WT;
		totalTAT+=p[i].TAT;
	}
	avg_WT=totalWT/n;
	avg_TAT=totalTAT/n;
	display(p);
	printf("\nthe average waiting time : %f",avg_WT);
	printf("\nthe average Turn Around time : %f",avg_TAT);
}

void SJF(struct process p[])
{
	totalWT=0;
	totalTAT=0;
	time =0;
	processed=0;
	
	struct process temp;
	while (processed!=n)
	{
		int shortest=-1;
		for(int i=0;i<n;i++)
		{
			if (p[i].flag==1)
			{ continue;}
			
			if(p[i].AT<=time)
			{
				if( shortest==-1)
				{
					shortest=i;
				}
				else if (p[i].BT<p[shortest].BT)
				{
					shortest=i;
				}
			}
		}
		if(shortest==-1)
		{
			for(int i=0;i<n;i++)
			{
				if (p[i].flag==0)
				{
					shortest=i;
					break;
				}
			}
		}
		if(p[shortest].AT>time)
		{
			time=p[shortest].AT;
		}
		else
		{
			p[shortest].WT=time-p[shortest].AT;
			totalWT+=p[shortest].WT;
			time+=p[shortest].BT;
			p[shortest].CT=time;
			p[shortest].TAT=time-p[shortest].AT;
			totalTAT+=p[shortest].TAT;
			p[shortest].flag=1;
			processed++;
		}
		
	}
	avg_WT=totalWT/n;
	avg_TAT=totalTAT/n;
	display(p);
	printf("\nthe average waiting time : %f",avg_WT);
	printf("\nthe average Turn Around time : %f",avg_TAT);
}


void priority(struct process p[])
{
	totalWT=0;
	totalTAT=0;
	time =0;
	processed=0;
	while (processed!=n)
	{
		int shortest=-1;
		for(int i=0;i<n;i++)
		{
			if (p[i].flag1==1)
			{ continue;}
			
			if(p[i].AT<=time)
			{
				if( shortest==-1)
				{
					shortest=i;
				}
				else if (p[i].prio<p[shortest].prio)
				{
					shortest=i;
				}
			}
		}
		if(shortest==-1)
		{
			for(int i=0;i<n;i++)
			{
				if (p[i].flag1==0)
				{
					shortest=i;
					break;
				}
			}
		}
		if(p[shortest].AT>time)
		{
			time=p[shortest].AT;
		}
		else
		{
			p[shortest].WT=time-p[shortest].AT;
			totalWT+=p[shortest].WT;
			time+=p[shortest].BT;
			p[shortest].CT=time;
			p[shortest].TAT=time-p[shortest].AT;
			totalTAT+=p[shortest].TAT;
			p[shortest].flag1=1;
			processed++;
		}
		
	}
	avg_WT=totalWT/n;
	avg_TAT=totalTAT/n;
	display(p);
	printf("\nthe average waiting time : %f",avg_WT);
	printf("\nthe average Turn Around time : %f",avg_TAT);
}

void RR(struct process p[],int slice)
{
	totalWT=0;
	totalTAT=0;
	time =0;
	processed=0;
	while (processed<n)
	{
		for(int i=0;i<n;i++)
		{
			if(p[i].RT>0)
			{
				if(p[i].RT>slice)
				{
					time+=slice;
					p[i].RT-=slice;
				}
				else
				{
					time+=p[i].RT;
					p[i].CT=time;
					p[i].TAT=p[i].CT-p[i].AT;
					p[i].WT=p[i].TAT-p[i].BT;
					p[i].RT=0;
					totalWT+=p[i].WT;
					totalTAT+=p[i].TAT;
					processed++;
				}
			}
		}
	}
	avg_WT=totalWT/n;
	avg_TAT=totalTAT/n;
	display(p);
	printf("\nthe average waiting time : %f",avg_WT);
	printf("\nthe average Turn Around time : %f",avg_TAT);
	
}
void main()
{
	struct process p[10];
	printf("enter number of process :");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("enter the process id :");
		scanf("%d",&p[i].pid);
		printf("enter the arrival time :");
		scanf("%d",&p[i].AT);
		printf("enter the Burst time :");
		scanf("%d",&p[i].BT);
		printf("enter the Priority :");
		scanf("%d",&p[i].prio);
		p[i].CT=0;
		p[i].flag=0;
		p[i].flag1=0;
		p[i].RT=p[i].BT;
	}
	
	sort(p);

	printf("\n\tP_ID\tAT\tBT\tPriority\n");
	printf("--------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
	{
		printf("\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].AT,p[i].BT,p[i].prio);
	}
	
	while(1)
	{
		printf("\n\n\n1.FCFS\n2.SJF\n3.Priority Scheduling\n4.round Robin\n5.Exit \nEnter Your Choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				FCFS(p);
				break;
			case 2:
				SJF(p);
				break;
			case 3:
				priority(p);
				break;
			case 4:
				printf("enter the time slice :");
				scanf("%d",&slice);
				RR(p,slice);
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid choice");
		}
	}
}