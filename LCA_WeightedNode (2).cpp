#include<stdio.h>
#include<string.h>
#include<utility>
#include<vector>
using namespace std;
#define MAXN 100
#define MAXLOG 30
vector < vector < int > > Edges(MAXN+6);
pair <int, int> dfstime[MAXN+6];
pair <int, int> LCA[MAXN+6][MAXLOG+6];
int Parent[MAXN+6];
int Level[MAXN+6], Weight[MAXN+6];
bool vis[MAXN+6];
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
    for (i=2; i<=N; ++i) LCA[i][0] = make_pair(Parent[i],Weight[i]);
    for (j=1; j<=LG; ++j)
    {
        for (i=1; i<=N; ++i)
        {
            if (LCA[i][j-1].first != -1) LCA[i][j] = make_pair(LCA[LCA[i][j-1].first][j-1].first, LCA[i][j-1].second + LCA[LCA[i][j-1].first][j-1].second);
        }
    }
}
void update(int N, int n, int val)
{
    int j;
    for (j=1; j<=LG; ++j)
    {
        if (LCA[n][j-1].first != -1) LCA[n][j] = make_pair(LCA[LCA[n][j-1].first][j-1].first, LCA[n][j-1].second + LCA[LCA[n][j-1].first][j-1].second);
    }
}
void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
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
    Parent[1] = -1;
    for (i=1; i<=N; ++i)
    {
        if (Level[i] > maxlevel) maxlevel = Level[i];
    }
    LG = calc(maxlevel);
}
int main()
{
    freopen("data.txt", "r", stdin);
    int N,i;
    pair <int,int> ans;
    int x,y;
    while(scanf("%d", &N) != EOF)
    {
        for (i=1; i<=N; ++i)
        {
            scanf("%d", &Weight[i]);
            Edges[i].clear();
        }
        for (i=1; i<N; ++i)
        {
            scanf("%d %d", &x, &y);
            //++x, ++y;
            Edges[x].push_back(y);
            Edges[y].push_back(x);
        }
        prepare(N);
        buildLCA(N);
        printLCA(N);
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
