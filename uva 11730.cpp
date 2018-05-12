#include<stdio.h>
#define MAX 1001
#define INF 32000
char sieve[MAX+3];
int prime_facts[MAX][20], pf[MAX]={0};
int dp[101][MAX+100];
int queue[MAX];
void prime_table()
{
    int i,j;
    for (i=4; i<MAX; i+=2)
    {
        prime_facts[i][pf[i]++] = 2;
        sieve[i] = 1;
    }
    for (i=3; i<MAX; i+=2)
    {
        if (!sieve[i])
        {
            for (j=i+i; j<MAX; j+=i)
            {
                prime_facts[j][pf[j]++] = i;
                sieve[j] = 1;
            }
        }
    }
}
void initialise()
{
    int i,j;
    for (i=0; i<101; i++)
    {
        for (j=0; j<MAX; j++) dp[i][j] = INF;
    }
}
void DP()
{
    int i,j,start,end,x,cost;
    for (i=1; i<101; i++)
    {
        start = end = 0;
        queue[end++] = i;
        dp[i][i] = 0;
        while(start<end)
        {
            for (j=0; j<pf[queue[start]]; j++)
            {
                x = queue[start] + prime_facts[queue[start]][j];
                cost = dp[i][queue[start]] + 1;
                if (x<MAX && dp[i][x]>cost)
                {
                    queue[end++] = x;
                    dp[i][x] = cost;
                }
            }
            start++;
        }
    }
}
int main()
{
    int s,t;
    int T = 1;
    prime_table();
    initialise();
    DP();
    while(scanf("%d%d",&s,&t))
    {
        if (!s && !t) break;
        if (dp[s][t] == INF) printf("Case %d: %d\n",T++,-1);
        else printf("Case %d: %d\n",T++,dp[s][t]);
    }
    return 0;
}
