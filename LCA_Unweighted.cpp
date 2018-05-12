// LCA Unweighted
#include<stdio.h>
#include<string.h>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 100
#define MAXLOG 30
vector < vector < int > > Edges(MAXN+3);
pair <int, int> dfstime[MAXN+3];
int LCA[MAXN+3][MAXLOG+3];
int Parent[MAXN+3];
int Level[MAXN+3];
bool vis[MAXN+3];
int Time, LG;
void dfs(int node, int level)
{
    vis[node] = true;
    Level[node] = level;
    int i, now, s = Time++;
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i];
        if (!vis[now])
        {
            Parent[now] = node;
            dfs(now, level+1);
        }
    }
    dfstime[node] = make_pair(s,Time++);
}
int calc(int l)
{
    int i;
    for (i=0; (1<<i)<=l; ++i); --i;
    return i;
}
void printLCA(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        for (j=0; j<=LG; ++j) printf("(%d) ",LCA[i][j]);
        puts("");
    }
}
void buildLCA(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        for (j=0; j<=LG; ++j) LCA[i][j] = -1;
    }
    for (i=1; i<=N; ++i) LCA[i][0] = Parent[i];
    for (j=1; j<=LG; ++j)
    {
        for (i=1; i<=N; ++i)
        {
            if (LCA[i][j-1] != -1) LCA[i][j] = LCA[LCA[i][j-1]][j-1];
        }
    }
}
int findLCA(int u, int v)
{
    if (u==v) return u;
    if (Level[u]<Level[v]) swap(u,v);
    int i,j;
    for (j=LG; j>=0; --j)
    {
        if (LCA[u][j] == -1) continue;
        if (Level[LCA[u][j]] >= Level[v]) u = LCA[u][j];
    }
    if (u==v) return u;
    for (j=LG; j>=0; --j)
    {
        if (LCA[u][j] != -1 && LCA[u][j] != LCA[v][j]) u = LCA[u][j], v = LCA[v][j];
    }
    return LCA[u][0];
}
void prepare(int N)
{
    memset(vis, false, sizeof(vis));
    Time = 1;
    dfs(1,1);
    int i, maxlevel=-1;
    Parent[1] = -1;
    for (i=1; i<=N; ++i)
    {
        if (Level[i] > maxlevel) maxlevel = Level[i];
    }
    LG = calc(maxlevel);
}
int main()
{
    int N,i;
    int ans;
    int x,y,c=1;
    while(scanf("%d", &N) != EOF)
    {
        for (i=1; i<=N; ++i) Edges[i].clear();
        for (i=1; i<N; ++i)
        {
            //scanf("%d %d %d", &x, &y, &c);
            scanf("%d %d", &x, &y);
            Edges[x].push_back(y);
            Edges[y].push_back(x);
        }
        prepare(N);
        buildLCA(N);
        while(scanf("%d %d", &x, &y) != EOF)
        {
            ans = findLCA(x,y);
            printf("%d : dist from root = %d\n", ans,Level[ans]);
        }
    }
    return 0;
}

/*
10
1 2
1 3
3 4
3 5
3 6
4 7
7 10
5 8
5 9
*/
