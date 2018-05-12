#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;
#define MAX 1500
vector < vector <int> > edges(MAX+3);
int parent[MAX+3];
int dp[MAX+3][2];
bool vis[MAX+3][2];
int f(int u, int stat)
{
    if(edges[u].size() == 0)return 0;
    if(vis[u][stat]) return dp[u][stat];
    vis[u][stat] = true;
    int ret = 0, i, v;
    for(i=0; i < edges[u].size(); i++)
    {
        v = edges[u][i];
        if(v != parent[u])
        {
            parent[v] = u;
            if(!stat) ret += f(v,1);
            else ret += min(f(v,1),f(v,0));
        }
    }
    return dp[u][stat] = ret + stat;
}
int main()
{
    int N,i,n,x,v,ans;
    while(scanf("%d", &N) != EOF)
    {
        for (i=0; i<=N; ++i) edges[i].clear();
        for (i=0; i<N; ++i)
        {
            scanf("%d:(%d)", &n, &x);
            while(x--)
            {
                scanf("%d", &v);
                edges[n].push_back(v);
                edges[v].push_back(n);
            }
        }
        memset(vis, false, sizeof(vis));
        ans = min(f(0,1),f(0,0));
        printf("%d\n",ans);
    }
    return 0;
}
