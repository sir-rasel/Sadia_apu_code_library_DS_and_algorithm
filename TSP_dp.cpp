#include<stdio.h>
#include<string.h>
#define INF 20000
#define MAXN 20
int n,k,save,umask;
int wt[MAXN][MAXN];
int dp[(1<<MAXN) + 6][MAXN];
bool vis[(1<<MAXN) + 6][MAXN];
int min (int a, int b)
{
    if (a<b) return a;
    else return b;
}
int dprec(int mask, int now)
{
    if (mask == umask) return 0;
    int i,x,nxt,ret=INF;
    if (vis[mask][now]) return dp[mask][now];
    vis[mask][now] = true;
    for (i=0; i<n; i++)
    {
        if (mask & (1<<i)) continue;
        x = wt[now][i] + dprec(mask|(1<<i),i);
        if (x < ret) ret = x;
    }
    return dp[mask][now] = ret;
}
int main()
{
    int i,j,p,cost,ans,mask;
    while(scanf("%d %d", &n, &k)!=EOF) // n = #nodes, k = #edges
    {
        save= INF;
        for (i=0; i<n; i++)
        {
            for (j=0; j<i; j++) wt[i][j] = wt[j][i] = INF;
            wt[i][i] = 0;
        }
        for (p=0; p<k; p++)
        {
            scanf("%d %d %d", &i, &j, &cost);
            wt[i][j] = wt[j][i] = cost;
        }
        memset(vis, false, sizeof(vis));
        umask = (1<<n) - 1;
        ans = dprec(1,0);
        printf("%d\n", ans);
    }
    return 0;
}

/*
5 6
0 1 3
1 2 1
0 2 4
0 3 5
3 4 6
2 4 2


5 5
0 1 1
1 2 2
2 3 3
3 4 4
4 0 5

5 6
0 1 3
1 4 4
0 4 2
0 2 1
2 3 6
3 4 5

5 10
0 1 3
1 3 2
3 2 5
2 4 4
0 4 1
0 3 11
0 2 15
1 4 12
3 4 10
1 2 14

5 10
0 1 23
1 3 22
3 2 25
2 4 24
0 4 21
0 3 11
0 2 15
1 4 12
3 4 10
1 2 14

10 20
0 1 1
1 2 2
2 3 3
3 4 4
4 5 5
5 6 6
6 7 7
7 8 8
8 9 9
9 0 1
0 1 11
1 2 22
2 3 33
3 4 44
5 7 43
7 3 44
5 9 88
0 5 9
8 3 55
9 5 6
*/
