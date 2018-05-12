// Tree DP
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<string>
#include<stack>
#include<queue>
using namespace std;
#define MAXSIZE 100
vector < vector < int > > Edges(MAXSIZE+6);
int cost[MAXSIZE+6][MAXSIZE+6];
int FChild[MAXSIZE+6], Sibling[MAXSIZE+6], Parent[MAXSIZE+6]={0,-1};
void bfs(int N)
{
    bool vis[MAXSIZE+6]={false};
    queue < int > Q;
    int now,nxt,fc,sib,i;
    while(!Q.empty()) Q.pop();
    Q.push(1); vis[1] = true;
    memset(FChild, -1, sizeof(FChild)); memset(Sibling, -1, sizeof(Sibling));
    while(!Q.empty())
    {
        now = Q.front();
        Q.pop();
        fc = sib = -1;
        for (i=0; i<Edges[now].size(); ++i)
        {
            nxt = Edges[now][i];
            if (vis[nxt]) continue;
            vis[nxt] = true;
            if (fc == -1) FChild[now] = nxt;
            if (sib != -1) Sibling[sib] = nxt;
            fc = sib = nxt;
            Parent[nxt] = now;
            Q.push(nxt);
        }
    }
    //for (i=1; i<=N; ++i) printf("%d : %d %d %d\n", i, FChild[i], Sibling[i], Parent[i]);
}
bool vis[MAXSIZE+6][MAXSIZE+6][3];
int dp[MAXSIZE+6][MAXSIZE+6][3], K;
int rec(int node, int k, int t)
{
    if (node == -1) return 0;
    if (vis[node][k][t]) return dp[node][k][t];
    vis[node][k][t] = true;
    int ret = MAXSIZE, temp, kk;
    int fc = FChild[node], sb = Sibling[node], p = Parent[node];
    if (t == 0)
    {
        if (p != -1 && cost[p][node] <= k)
        {
            temp = rec(node, k-cost[p][node], 1);
            if (ret > temp) ret = temp;
        }
        temp = 1 + rec(node, K, 2) + rec(sb, k, 0);
        if (ret > temp) ret = temp;
    }
    else if (t == 1)
    {
        for (kk=0; kk<=k; ++kk)
        {
            temp = rec(fc, kk, 0) + rec(sb, k-kk, 0);
            if (ret > temp) ret = temp;
        }
    }
    else
    {
        temp = rec(fc, K, 0);
        if (ret > temp) ret = temp;
    }
    //printf("%d %d %d : %d\n", node, k, t, ret);
    return dp[node][k][t] = ret;
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int t,T;
    int N,i;
    int x,y,c;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d %d", &N, &K);
        for (i=1; i<=N; ++i) Edges[i].clear();
        for (i=1; i<N; ++i)
        {
            scanf("%d %d %d", &x, &y, &c);
            Edges[x].push_back(y);
            Edges[y].push_back(x);
            cost[x][y] = cost[y][x] = c;
        }
        bfs(N); //puts("");
        memset(vis, false, sizeof(vis));
        printf("Case %d: %d\n", t, rec(1,K,0));
    }
    return 0;
}
