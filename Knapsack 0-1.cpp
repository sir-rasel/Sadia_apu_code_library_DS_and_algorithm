#include<stdio.h>
#define MAX 1003
int knapsack[MAX][MAX];
int value[MAX],weight[MAX];
int max (int a, int b)
{
    if (a>b) return a;
    else return b;
}
int main()
{
    int n,i,j,maxweight;
    while(scanf("%d",&n)!=EOF)
    {
        for (i=1; i<=n; i++) scanf("%d%d",&value[i],&weight[i]);
        scanf("%d",&maxweight);
        for (i=0; i<=maxweight; i++) knapsack[0][i] = 0;
        for (i=0; i<=n; i++) knapsack[i][0] = 0;
        for (i=1; i<=n; i++)
        {
            for (j=1; j<=maxweight; j++)
            {
                if (weight[i]>j) knapsack[i][j] = knapsack[i-1][j];
                else knapsack[i][j] = max(knapsack[i-1][j], knapsack[i-1][j-weight[i]]+value[i]);
            }
        }
        printf("%d\n",knapsack[n][maxweight]);
    }
    return 0;
}
