#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define SIZE 50
struct edge
{
    int to;
    bool status;
    edge() {status = false;}
    edge(int t, bool s) {to = t, status = s;}
};
bool cmp(edge a, edge b) {return a.to < b.to;}
vector < vector <edge> > V ((SIZE<<1)+3);
int MatchRow[SIZE+3];
bool vis[(SIZE<<1)+3];
int findIndx(int now, int node)
{
    int low = 0, high = V[now].size()-1, mid;
    while(low<high)
    {
        mid = (low+high)>>1;
        if (V[now][mid].to == node) return mid;
        if (V[now][mid].to >= node) high = mid;
        else low = mid + 1;
    }
    return low;
}
bool dfs(int N, int node)
{
    if (node == N) return true;
    if (vis[node]) return false;
    vis[node] = true;
    int i,j,now;
    for (i=0; i<V[node].size(); ++i)
    {
        now = V[node][i].to;
        if (V[node][i].status && dfs(N,now))
        {
            V[node][i].status = false;
            if (node<=(N>>1)) MatchRow[node-1] = now-(N>>1)-1;
            j = findIndx(now, node);
            V[now][j].status = true;
            return true;
        }
    }
    return false;
}
int findMatch(int N)
{
    int ret = 0;
    memset(vis, false, sizeof(vis));
    int i, n = N>>1;
    while(dfs(N,0))
    {
        ++ret;
        memset(vis, false, sizeof(vis));
    }
    for (i=0; i<n; ++i) printf("%d %d\n", i,MatchRow[i]);
    return ret;
}
int matrix[SIZE+3][SIZE+3];
void buildGraph(int N)
{
    int i,j;
    int LIM = N<<1;
    for (i=0; i<=LIM+1; ++i) V[i].clear();
    for (i=0; i<N; ++i)
    {
        V[0].push_back(edge(i+1,true));
        V[i+1].push_back(edge(0,false));
        for (j=0; j<N; ++j)
        {
            if (matrix[i][j]==0)
            {
                V[i+1].push_back(edge(N+j+1,true));
                V[N+j+1].push_back(edge(i+1,false));
            }
        }
    }
    for (i=0; i<N; ++i)
    {
        V[LIM+1].push_back(edge(N+i+1,false));
        V[N+i+1].push_back(edge(LIM+1,true));
    }
}
void takeInput(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) scanf("%d", &matrix[i][j]);
    }
}
void printList(int N)
{
    int i,j;
    for (i=0; i<=N; ++i)
    {
        printf("%d : ",i);
        for (j=0; j<V[i].size(); ++j) printf ("(%d %d) ", V[i][j].to, V[i][j].status);
        puts("");
    }
    puts("------------------------------------");
}
int main()
{
    int N;
    while(scanf("%d", &N)!=EOF && N)
    {
        takeInput(N);
        buildGraph(N);
        //printList(2*N+1);
        printf("%d\n",findMatch((N<<1)+1));
    }
    return 0;
}
