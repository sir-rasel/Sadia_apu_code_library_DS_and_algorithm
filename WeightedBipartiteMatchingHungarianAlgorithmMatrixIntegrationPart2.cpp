#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define SIZE 50
#define INF 100000
struct edge
{
    int to;
    bool status;
    edge() {status = false;}
    edge(int t, bool s) {to = t, status = s;}
};
vector < vector <edge> > V ((SIZE<<1)+3);
int matrix[SIZE+3][SIZE+3], original[SIZE+3][SIZE+3];
//bool RowMark[SIZE+3], ColMark[SIZE+3];
int RowLeft[SIZE+3];
int MatchRow[SIZE+3];
bool tickedRow[SIZE+3], tickedCol[SIZE+3];
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
bool vis[(SIZE<<1)+3];
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
            for (j=0; j<V[now].size(); ++j)
            {
                if (V[now][j].to == node)
                {
                    V[now][j].status = true;
                    return true;
                }
            }
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
void buildGraph(int N)
{
    int i,j;
    int LIM = N<<1;
    for (i=0; i<=LIM+1; ++i) V[i].clear();
    for (i=0; i<N; ++i)
    {
        V[0].push_back(edge(i+1,true));
        V[i+1].push_back(edge(0,false));
        V[LIM+1].push_back(edge(N+i+1,false));
        V[N+i+1].push_back(edge(LIM+1,true));
        for (j=0; j<N; ++j)
        {
            if (matrix[i][j]==0)
            {
                V[i+1].push_back(edge(N+j+1,true));
                V[N+j+1].push_back(edge(i+1,false));
            }
        }
    }
}
void minRowDel(int N)
{
    int i,j,mini;
    for (i=0; i<N; ++i)
    {
        mini = INF;
        for (j=0; j<N; ++j)
        {
            if (matrix[i][j]<mini) mini = matrix[i][j];
        }
        for (j=0; j<N; ++j) matrix[i][j] -= mini;
    }
}
void minColDel(int N)
{
    int i,j,mini;
    for (j=0; j<N; ++j)
    {
        mini = INF;
        for (i=0; i<N; ++i)
        {
            if (matrix[i][j]<mini) mini = matrix[i][j];
        }
        for (i=0; i<N; ++i) matrix[i][j] -= mini;
    }
}
void nowCol(int, int);
void nowRow(int N, int r)
{
    if (tickedRow[r]) return;
    tickedRow[r] = true;
    int j;
    for (j=0; j<N; ++j)
    {
        if (matrix[r][j]==0) nowCol(N,j);
    }
}
void nowCol(int N, int c)
{
    if (tickedCol[c]) return;
    tickedCol[c] = true;
    int i;
    for (i=0; i<N; ++i)
    {
        if (MatchRow[i] == c)
        {
            nowRow(N,i);
            break;
        }
    }
}
void findTicks(int N)
{
    int i,j;
    memset(tickedRow, false, sizeof(tickedRow));
    memset(tickedCol, false, sizeof(tickedCol));
    for (i=0; i<N; ++i)
    {
        if (MatchRow[i]==-1) nowRow(N,i);
    }
}
int findTheta(int N)
{
    int i,j,mini = INF;
    for (i=0; i<N; ++i)
    {
        if (!tickedRow[i]) continue;
        for (j=0; j<N; ++j)
        {
            if (tickedCol[j]) continue;
            if (matrix[i][j])
            {
                if (matrix[i][j] && matrix[i][j]<mini) mini = matrix[i][j];
            }
        }
    }
    return mini;
}
void adjTheta(int N, int theta)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            if (!tickedRow[i] && tickedCol[j]) matrix[i][j] += theta;
            else if (!tickedRow[i] || tickedCol[j]) continue;
            else matrix[i][j] -= theta;
        }
    }
}
int countLines(int N)
{
    int ret = 0, i;
    for(i=0; i<N; ++i)
    {
        if (!tickedRow[i]) ++ret;
        if (tickedCol[i]) ++ret;
    }
    return ret;
}
int findMax(int N)
{
    int i,j,ret = -INF;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            if (matrix[i][j]>ret) ret = matrix[i][j];
        }
    }
    return ret;
}
int match(int N)
{
    minRowDel(N);
    minColDel(N);
    buildGraph(N);
    int found = findMatch((N<<1)+1);
    findTicks(N);
    int i,j,ret=0,theta;
    while(found != N)
    {
        theta = findTheta(N);
        adjTheta(N, theta);
        findTicks(N);
        found = findMatch((N<<1)+1);
    }
    for (i=0; i<N; ++i)
    {
       // printf("%d %d\n", i, MatchRow[i]);
        ret += original[i][MatchRow[i]];
    }
    return ret;
}
void takeInput(int N)
{
    int i,j,maxi=-1;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            scanf("%d", &original[i][j]);
            if (original[i][j]>maxi) maxi = original[i][j];
        }
    }
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) matrix[i][j] = maxi - original[i][j];
    }
}
int main()
{
    //freopen("data1.txt", "r", stdin);
    int t,T;
    int N;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        takeInput(N);
        printf("Case %d: %d\n", t, match(N));
    }
    return 0;
}
