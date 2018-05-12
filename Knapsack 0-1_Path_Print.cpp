#include<stdio.h>
#include<algorithm>
using namespace std;
#define MAX 1003
int knapsack[MAX];
struct inputs
{
    int value;
    int weight;
} input[MAX];
int save[MAX][MAX];
int t[MAX];
int max (int a, int b)
{
    if (a>b) return a;
    else return b;
}
int main()
{
    int n,i,j,k,maxweight,T,w,f=0;
    while(scanf("%d%d",&T,&w)!=EOF)
    {
        if (!f) f++;
        else puts("");
        scanf("%d",&n);
        for (i=1; i<=n; i++)
        {
            scanf("%d%d",&input[i].weight,&input[i].value);
            input[i].weight *= (3*w);
        }
        maxweight = T;
        for (i=0; i<=maxweight; i++)
        {
            t[i]=0;
            knapsack[i] = 0;
        }
        for (i=1; i<=n; i++)
        {
            for (j=maxweight; j>0; j--)
            {
                if (input[i].weight>j || knapsack[j-1]>knapsack[j-input[i].weight]+input[i].value)
                {
                    knapsack[j] = knapsack[j-1];
                    for (k=0; k<t[j-1]; k++) save[j][k] = save[j-1][k];
                    t[j] = t[j-1];
                }
                else
                {
                    knapsack[j] = knapsack[j-input[i].weight]+input[i].value;
                    int p = j-input[i].weight;
                    for (k=0; k<t[p]; k++) save[j][k] = save[p][k];
                    save[j][k] = i;
                    t[j] = t[p]+1;
                }
            }
        }
        printf("%d\n%d\n",knapsack[maxweight],t[maxweight]);
        sort(save[maxweight], save[maxweight]+t[maxweight]);
        for (i=0; i<t[maxweight]; i++)
        {
            printf("%d %d\n",input[save[maxweight][i]].weight/(3*w),input[save[maxweight][i]].value);
        }
    }
    return 0;
}
