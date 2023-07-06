//Prajwal 
#include<stdio.h>
#include<stdlib.h>
int diskQueue[20], n ,start;

void fcfs()
{	int i, seekTime=0, diff;
	printf("Movement of cylinders\n");
	for(int i=0; i<n; i++)
	{	diff = abs(diskQueue[i+1]-diskQueue[i]);
		printf("Move from %d to %d with seek time %d\n", diskQueue[i], diskQueue[i+1], diff);
		seekTime+=diff;
	}
	printf("Total seek time: %d \n", seekTime);

}

void sstf()
{	int visited[20], sstf_disk[20],i, seekTime=0, temp_start = start;
	for(i=0; i<n; i++)
	{	sstf_disk[i] = diskQueue[i];
	}
	for(i=0; i<n; i++)
	{	visited[i]=0;
	}
	int remaining_requests = n-1;
	while(remaining_requests)
	{	int min=1777777;
		int min_track_number, position;
		for(i=1; i<=n; i++)
		{	if( abs(temp_start - sstf_disk[i]) < min && visited[i]==0)
			{	min = abs(temp_start - sstf_disk[i]);
				min_track_number = sstf_disk[i];
				position = i;
			}
		}
		printf("Seek time from %d to %d is %d \n", temp_start, min_track_number, min);
		temp_start = sstf_disk[position];
		visited[position] = 1;
		seekTime+=min;
		remaining_requests--;
	}
	printf("Seek time is %d \n", seekTime);
}

void sort(int disk[20], int n)
{	int i,j, temp;
	for(i-0; i<n-1; i++)
	{	for(j=0; j<n-i-1; j++)
		{	if(disk[j]>disk[j+1])
			{	temp=disk[j];
				disk[j] = disk[j+1];
				disk[j+1] = temp;
			}
		}
	}
}

void scan()
{	int scan_disk[20], previous;
	int i,pos,diff,seekTime=0, current;
	for(i=0; i<n; i++)
	{	scan_disk[i] = diskQueue[i];
	}
	sort(scan_disk, n);
	for(i=0; i<n; i++)
	{	if(scan_disk[i]==start)
		{	pos=i;
			break;
		}
	}
	printf("Enter previous head position: ");
	scanf("%d", &previous);
	printf("Movement of cylinder\n");
	if(start<previous)
	{	seekTime=0;
		for(i=pos; i>0; i--)
		{	diff = abs(scan_disk[i]-scan_disk[i-1]);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", scan_disk[i], scan_disk[i-1], diff);
		}
		diff = scan_disk[0];
		seekTime+=diff;
		printf("Move from %d to 0 with seek time %d\n", scan_disk[0], diff);
		current=0;
		for(i=pos+1; i<n; i++)
		{	diff=abs(scan_disk[i] - current);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", current, scan_disk[i], diff);
			current=scan_disk[i];
		}
	}
	else
	{	seekTime=0;
		for(i=pos; i<n-1; i++)
		{	diff=abs(scan_disk[i+1] - scan_disk[i]);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", scan_disk[i], scan_disk[i+1], diff);
		}
		diff = 199 - scan_disk[n-1];
		seekTime+=diff;
		printf("Move from %d to 199 with seek time %d\n", scan_disk[n-1], diff);
		current=199;
		for(i=pos-1; i>=0; i--)
		{	diff=abs(scan_disk[i]-current);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", current, scan_disk[i], diff);
			current=scan_disk[i];
		}
	}
	printf("Total seek time: %d ", seekTime);
	
}

void cscan()
{	int cscan_disk[20];
	int i, pos, diff, seekTime=0, current;
	int previous;
	printf("Enter previous head position: ");
	scanf("%d", &previous);
	for(i=0; i<n; i++)
	{	cscan_disk[i]=diskQueue[i];
	}
	sort(cscan_disk, n);
	for(i=0; i<n; i++)
	{	if(cscan_disk[i]==start)
		{	pos=i;
			break;
		}
	}
	printf("Movement of cylinder\n");
	if(start<previous)
	{	
		for(i=pos; i>0; i--)
		{	diff = abs(cscan_disk[i]-cscan_disk[i-1]);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", cscan_disk[i], cscan_disk[i-1], diff);
		}
		current=0;
		diff = cscan_disk[0]-current;
		seekTime+=diff;
		printf("Move from %d to 0 with seek time %d\n", cscan_disk[0], diff);
		current=199;
		diff=current;
		seekTime+=diff;
		printf("Move from 0 to 199 with seek time %d\n", diff);
		for(i=n-1; i>pos; i--)
		{	diff=abs(cscan_disk[i] - current);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", current, cscan_disk[i], diff);
			current=cscan_disk[i];
		}
	}
	else
	{	
		for(i=pos; i<n-1; i++)
		{	diff=abs(cscan_disk[i+1] - cscan_disk[i]);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", cscan_disk[i], cscan_disk[i+1], diff);
		}
		current=199;
		diff = 199 - cscan_disk[n-1];
		seekTime+=diff;
		printf("Move from %d to 199 with seek time %d\n", cscan_disk[n-1], diff);
		current=0;
		diff=199;
		seekTime+=diff;
		printf("Move from 199 to 0 with seek time %d\n", diff);
		for(i=0; i<pos; i++)
		{	diff=abs(cscan_disk[i]-current);
			seekTime+=diff;
			printf("Move from %d to %d with seek time %d\n", current, cscan_disk[i], diff);
			current=cscan_disk[i];
		}
	}
	printf("Total seek time: %d ", seekTime);
}

void main()
{	int i,c;
	printf("Enter no of requests: ");
	scanf("%d", &n);
	printf("Enter the requests: ");
	for(i=1; i<=n; i++)
	{	scanf("%d", &diskQueue[i]);
	}
	printf("Enter initial head position: ");
	scanf("%d", &diskQueue[0]);
	start=diskQueue[0];
	do{	
		printf("Enter choice \n1.FCFS \n2.SSTF \n3.SCAN \n4.CSCAN \n5.Exit \n");
		scanf("%d", &c);
		switch(c)
		{	case 1:	fcfs();
					break;
			case 2:	++n;
					sstf();
					--n;
					break;
			case 3:	++n;
					scan();
					--n;
					break;
			case 4:	++n;
					cscan();
					--n;
					break;
			case 5:	break;
			default:	printf("Enter valid choice\n");
					break;
		}
	}while(c!=5);
	
}

/*OUTPUT
Enter no of requests: 7
Enter the requests: 82 170 43 140 24 16 190
Enter initial head position: 50
Enter choice 
1.FCFS 
2.SSTF 
3.SCAN 
4.CSCAN 
5.Exit 
1
Movement of cylinders
Move from 50 to 82 with seek time 32
Move from 82 to 170 with seek time 88
Move from 170 to 43 with seek time 127
Move from 43 to 140 with seek time 97
Move from 140 to 24 with seek time 116
Move from 24 to 16 with seek time 8
Move from 16 to 190 with seek time 174
Total seek time: 642 
Enter choice 
1.FCFS 
2.SSTF 
3.SCAN 
4.CSCAN 
5.Exit 
2
Seek time from 50 to 43 is 7 
Seek time from 43 to 24 is 19 
Seek time from 24 to 16 is 8 
Seek time from 16 to 82 is 66 
Seek time from 82 to 140 is 58 
Seek time from 140 to 170 is 30 
Seek time from 170 to 190 is 20 
Seek time is 208 
Enter choice 
1.FCFS 
2.SSTF 
3.SCAN 
4.CSCAN 
5.Exit 
3
Enter previous head position: 20
Movement of cylinder
Move from 50 to 82 with seek time 32
Move from 82 to 140 with seek time 58
Move from 140 to 170 with seek time 30
Move from 170 to 190 with seek time 20
Move from 190 to 199 with seek time 9
Move from 199 to 43 with seek time 156
Move from 43 to 24 with seek time 19
Move from 24 to 16 with seek time 8
Total seek time: 332 Enter choice 
1.FCFS 
2.SSTF 
3.SCAN 
4.CSCAN 
5.Exit 
4
Enter previous head position: 20
Movement of cylinder
Move from 50 to 82 with seek time 32
Move from 82 to 140 with seek time 58
Move from 140 to 170 with seek time 30
Move from 170 to 190 with seek time 20
Move from 190 to 199 with seek time 9
Move from 199 to 0 with seek time 199
Move from 0 to 16 with seek time 16
Move from 16 to 24 with seek time 8
Move from 24 to 43 with seek time 19
Total seek time: 391  */








