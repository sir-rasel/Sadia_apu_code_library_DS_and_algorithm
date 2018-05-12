#include<stdio.h>
#include<conio.h>

#define MAX 100

unsigned long long partition[MAX][MAX]={0};

int main()
{
	int i,j,m;
	for(i=1;i<=MAX;i++)
		partition[0][i]=1;
	for(i=1;i<=MAX;i++)
	{
		for(j=1;j<=i;j++)
		{
			if(j==1)
			{
				partition[i][j]=1;
				continue;
			}
			if(i==j)
			{
				partition[i][j]=(partition[i][j-1]+1);
				continue;
			}
			for(m=i;m>=0;m-=j)
			{
				if(m==0)
					partition[i][j]+=1;
				else if(m>j-1)
					partition[i][j]+=partition[m][j-1];
				else
					partition[i][j]+=partition[m][m];
			}
		}
		printf("%d %lld\n",i,partition[i][i]);
		//for(int k=1;k<=i;k++)
		//	printf("%lld  ",partition[i][k]);
		//printf("\n");
	}
	getch();
	return 0;
}
