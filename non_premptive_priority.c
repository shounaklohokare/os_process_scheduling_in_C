 #include<stdio.h>
#include<stdlib.h>
#define SIZE 20

struct process
{
	int pn,at,bt,ct,priority,tat,wt,rt;
};

struct gantt
{
	int pn,st,ct;
};

struct process p[SIZE];
struct gantt g[SIZE];

float sumtat=0.0,sumwt=0.0;
int cur=0;

void getPCB(int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		p[i].pn=i;

		printf("\nEnter arrival time for process %d:",i);
		scanf("%d",&p[i].at);

		printf("\nEnter burst time for process %d:",i);
		scanf("%d",&p[i].bt);

		printf("\nEnter priority for process %d:",i);
		scanf("%d",&p[i].priority);
	}
}

void putPCB(int n)
{	
	int i;
	printf("PID\tAT\tBT\tCT\tRT\tWT\tTAT\n");
	for(i=1;i<=n;i++)
	{
		p[i].rt=p[i].wt;
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pn,p[i].at,p[i].bt,p[i].ct,p[i].rt,p[i].wt,p[i].tat);
	}
}

void sortAT(int n)
{
	int i,j;
	struct process temp;
		
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(p[i].at>p[j].at)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}
}

int getSJ(int n)
{	
	int i,j,min=9999;
	for(i=1;i<=n;i++)
	{
		if(p[i].priority<min && p[i].ct==0 && p[i].at<=cur)
		{
			min=p[i].priority;
			j=i;
		}
	}
	return j;
}	

void setGannt(int n)	
{
	int i,sjpos,j;
	for(i=1;i<=n;i++)	
	{
		g[i].pn==p[i].pn;
		if(p[i].at>cur)
		{
			p[i].ct=p[i].at+p[i].bt;
			cur=p[i].ct;
			p[i].tat=p[i].ct-p[i].at;
			p[i].wt=p[i].tat-p[i].bt;
			g[i].st=p[i].at;
			g[i].ct=p[i].ct;
		}
		else
		{
			sjpos=getSJ(n);
			p[sjpos].ct=cur + p[sjpos].bt;
			cur=p[sjpos].ct;
			p[sjpos].tat=p[sjpos].ct-p[sjpos].at;
			p[sjpos].wt=p[sjpos].tat-p[sjpos].bt;
			g[i].pn=p[sjpos].pn;
			g[i].st=cur-p[sjpos].bt;
			g[i].ct=p[sjpos].ct;
		}
	}
}

void putgantt(int n)
{
	int i;
	printf("\nGantt Chart\n");
	for(i=1;i<=n;i++)
	{
		printf("|%d  P%d   %d|",g[i].st,g[i].pn,g[i].ct);
	}
}	


void putavgtat(int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		sumtat=sumtat+(float)p[i].tat;
	}
	printf("\nAverage TAT=%2f",(sumtat/n));
}

void putavgwt(int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		sumwt=sumwt+(float)p[i].wt;
	}
	printf("\nAverage WT=%2f\n",(sumwt/n));
}

int main()
{
	int n,i;
	printf("\nEnter no. of processes:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		p[i].ct=0;
	}
	getPCB(n);
	sortAT(n);
	setGannt(n);
	putPCB(n);
	putgantt(n);
	putavgtat(n);
	putavgwt(n);
	return 0;
}


/*

Enter no. of processes:6

Enter arrival time for process 1:12

Enter burst time for process 1:7

Enter priority for process 1:5

Enter arrival time for process 2:1

Enter burst time for process 2:4

Enter priority for process 2:1

Enter arrival time for process 3:0

Enter burst time for process 3:3

Enter priority for process 3:2

Enter arrival time for process 4:2

Enter burst time for process 4:4

Enter priority for process 4:1

Enter arrival time for process 5:8

Enter burst time for process 5:7

Enter priority for process 5:2

Enter arrival time for process 6:14

Enter burst time for process 6:2

Enter priority for process 6:4
PID     AT      BT      CT      RT      WT      TAT

3       0       3       3       0       0       3

2       1       4       7       2       2       6

4       2       4       11      5       5       9

5       8       7       18      3       3       10

1       12      7       27      8       8       15

6       14      2       20      4       4       6

Gantt Chart
|0  P3   3||3  P2   7||7  P4   11||11  P5   18||18  P6   20||20  P1   27|
Average TAT=8.166667
Average WT=3.666667
*/
		
