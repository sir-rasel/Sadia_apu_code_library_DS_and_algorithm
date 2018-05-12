#include<stdio.h>
#include<string.h>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 100
#define MAXLOG 30
vector < vector < pair <int, int> > > Edges(MAXN+3);
pair <int, int> dfstime[MAXN+3];
pair <int, int> LCA[MAXN+3][MAXLOG+3];
pair <int, int> Parent[MAXN+3];
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
        now = Edges[node][i].first;
        if (!vis[now])
        {
            Parent[now] = make_pair(node, Edges[node][i].second);
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
        for (j=0; j<=LG; ++j) printf("(%d %d) ",LCA[i][j].first, LCA[i][j].second);
        puts("");
    }
}
void buildLCA(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        for (j=0; j<=LG; ++j) LCA[i][j] = make_pair(-1,0);
    }
    for (i=1; i<=N; ++i) LCA[i][0] = Parent[i];
    for (j=1; j<=LG; ++j)
    {
        for (i=1; i<=N; ++i)
        {
            if (LCA[i][j-1].first != -1) LCA[i][j] = make_pair(LCA[LCA[i][j-1].first][j-1].first, LCA[i][j-1].second + LCA[LCA[i][j-1].first][j-1].second);
        }
    }
}
pair <int, int> findLCA(int N, int u, int v)
{
    if (u==v) return make_pair(u,0);
    if (Level[u]<Level[v]) swap(u,v);
    int i,j, ret=0;
    for (j=LG; j>=0; --j)
    {
        if (LCA[u][j].first == -1) continue;
        if (Level[LCA[u][j].first] >= Level[v])
        {
            ret += LCA[u][j].second;
            u = LCA[u][j].first;
        }
    }
    if (u==v) return make_pair(u,ret);
    for (j=LG; j>=0; --j)
    {
        if (LCA[u][j].first != -1 && LCA[u][j].first != LCA[v][j].first)
        {
            ret += LCA[u][j].second + LCA[v][j].second;
            u = LCA[u][j].first, v = LCA[v][j].first;
        }
    }
    ret += LCA[u][0].second + LCA[v][0].second;
    return make_pair(LCA[u][0].first, ret);
}
void prepare(int N)
{
    memset(vis, false, sizeof(vis));
    Time = 1;
    dfs(1,1);
    int i, maxlevel=-1;
    Parent[1] = make_pair(-1,0);
    for (i=1; i<=N; ++i)
    {
        if (Level[i] > maxlevel) maxlevel = Level[i];
    }
    LG = calc(maxlevel);
}
int main()
{
    int N,i;
    pair <int,int> ans;
    int x,y,c=1;
    while(scanf("%d", &N) != EOF)
    {
        for (i=1; i<=N; ++i) Edges[i].clear();
        for (i=1; i<N; ++i)
        {
            //scanf("%d %d %d", &x, &y, &c);
            scanf("%d %d", &x, &y);
            Edges[x].push_back(make_pair(y,c));
            Edges[y].push_back(make_pair(x,c));
        }
        prepare(N);
        buildLCA(N);
        while(scanf("%d %d", &x, &y) != EOF)
        {
            ans = findLCA(N,x,y);
            printf("%d %d\n", ans.first, ans.second);
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
