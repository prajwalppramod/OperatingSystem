#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int used[10];

bool found(int a[], int n, int x)
{	for(int i=0; i<n; i++)
	{	if(a[i]==x)
		{	return true;
		}
	}
	return false;
}

void display(int a[], int n, int count)
{	if(count<n)
	{	for(int i=0; i<count; i++)
		{	printf("%d", a[i]);
		}
	}
	else
	{	for(int i=0; i<n; i++)
		{	printf("%d", a[i]);
		}
	}
}

int findLRU(int frames[], int used[], int nframes)
{	int i, min=used[0], minIndex=0;
	for(int i=0; i<nframes; i++)
	{	if(used[i]<min)
		{	min=used[i];
			minIndex=i;
		}
	}
	return minIndex;
}

void fifo(int ref[], int n_frames, int n)
{	int count=0, index=0, frame[8];
	printf("\nref_string\t\tframe\t\tstatus");
	for(int i=0; i<n_frames; i++)
	{	frame[i]=-1;
	}
	for(int i=0; i<n;i++)
	{	if(found(frame,n_frames,ref[i]))
		{	printf("\n\t%d\t\t", ref[i]);
			display(frame, n_frames, count);
			printf("\t\thit");
		}
		else
		{	frame[index]=ref[i];
			index=(index+1)%n_frames;
			count++;
			printf("\n\t%d\t\t", ref[i]);
			display(frame, n_frames, count);
			printf("\t\tmiss");
		}
	}
	printf("\nNo of page fault is %d", count);
}

void LRU(int ref[], int n_frames, int n)
{	int count=0, index=0, frame[8], used[10];
	for(int i=0; i<n_frames; i++)
	{	used[i]=0;
		frame[i]=-1;
	}
	printf("\nLRU Page Replacement");
	printf("\nref_string\t\tframe\t\t\tstatus\n");
	for(int i=0; i<n; i++)
	{	int found=0;
		for(int j=0; j<n_frames; j++)
		{	if(frame[j]==ref[i])
			{	found=1;
				used[j]=i+1;
				break;
			}
		}
	
		if(found==0)
		{	int lruIndex = findLRU(frame, used, n_frames);
			frame[lruIndex]=ref[i];
			used[lruIndex]=i+1;
			count++;
			printf("\t%d\t\t", ref[i]);
			display(frame, n_frames,count);
			printf("\t\t\tmiss\n");
		}
		else
		{	printf("\n\t%d\t\t", ref[i]);
			display(frame,n_frames,count);
			printf("\t\t\thit\n");		
		}
	}
	printf("\nNo of page fault is %d", count);
}

int findReplacement(int ref[], int n, int frame[], int n_frames, int i)
{	int replaceIndex=-1, max_future_index=-1;
	for(int j=0; j<n_frames; j++)
	{	bool found_future=false;
		for(int k=i+1; k<n; k++)
		{	if(ref[k]==frame[j])
			{	found_future=true;
				if(k>max_future_index)
				{	max_future_index=k;
					replaceIndex=j;
				}
			}
			break;
		}
	}
	return replaceIndex;
}

void OPR(int ref[], int n_frames, int n)
{	int count=0, index=0, frame[8];
	for(int i=0; i<n_frames; i++)
	{	frame[i]=-1;
	}
	printf("\nref_string\t\tframe\t\t\tstatus");
	int numOccupiedFrames=0;
	for(int i=0; i<n ;i++)
	{	if(found(frame,n_frames,ref[i]))
		{	printf("\n\t%d\t\t", ref[i]);
			display(frame, n_frames, count);
			printf("\t\t\thit");
		}
		else
		{	int replace_index=-1;
			if(count<n_frames)
			{	replace_index=count;
			}
			else
			{	replace_index=findReplacement(ref,n,frame,n_frames,i);
			}
			frame[replace_index]=ref[i];
			count++;
			printf("\n\t%d\t\t",ref[i]);
			display(frame, n_frames, count);
			printf("\t\t\tmiss");
		}
	}
	printf("\nNo of page fault is %d", count);
}

void main()
{	int n, n_frames, choice, ref[30];
	printf("Enter no of elements in reference string: ");
	scanf("%d", &n);
	printf("Enter elements of reference string: \n");
	for(int i=0; i<n; i++)
	{	scanf("%d", &ref[i]);
	}
	printf("Enter no of frames: ");
	scanf("%d", &n_frames);
	while(true)
	{	printf("\n1.FIFO \t2.LRU \t3.Optimal \t4.Exit\n");
		scanf("%d", &choice);
		switch(choice)
		{	case 1:	fifo(ref, n_frames,n);
					break;
			case 2:	LRU(ref, n_frames, n);
					break;
			case 3:	OPR(ref, n_frames,n);
			case 4:	break;
			default:	printf("Enter valid choice");
		}
	}
}

