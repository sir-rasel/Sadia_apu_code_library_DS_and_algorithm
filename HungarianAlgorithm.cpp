// Hungarian Algorithm
#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define SIZE 53
#define INF 100000
struct edge
{
    int to;
    bool status;
    edge(int t, bool s) {to = t, status = s;}
};
vector < vector <edge> > V ((SIZE<<1));
int matrix[SIZE][SIZE], original[SIZE][SIZE];
bool vis[(SIZE<<1)];
int RowLeft[SIZE];
int MatchRow[SIZE];
bool TickedRow[SIZE], TickedCol[SIZE];
void initReuse(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) original[i][j] =  matrix[i][j];
    }
}
void printList(int N)
{
    int i,j;
    puts("------------------------------------");
    for (i=0; i<=N; ++i)
    {
        printf("%d : ",i);
        for (j=0; j<V[i].size(); ++j) printf ("(%d %d) ", V[i][j].to, V[i][j].status);
        puts("");
    }
    puts("------------------------------------");
}
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
    for (i=0; i<(N>>1); ++i) MatchRow[i] = -1;
    while(dfs(N,0))
    {
        ++ret;
        memset(vis, false, sizeof(vis));
    }
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
    if (TickedRow[r]) return;
    TickedRow[r] = true;
    int j;
    for (j=0; j<N; ++j)
    {
        if (matrix[r][j]==0) nowCol(N,j);
    }
}
void nowCol(int N, int c)
{
    if (TickedCol[c]) return;
    TickedCol[c] = true;
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
    memset(TickedRow, false, sizeof(TickedRow));
    memset(TickedCol, false, sizeof(TickedCol));
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
        if (!TickedRow[i]) continue;
        for (j=0; j<N; ++j)
        {
            if (TickedCol[j]) continue;
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
            if (!TickedRow[i] && TickedCol[j]) matrix[i][j] += theta;
            else if (!TickedRow[i] || TickedCol[j]) continue;
            else matrix[i][j] -= theta;
        }
    }
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
void printMatrix(int N)
{
    int i,j;
    puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) printf("%3d ", matrix[i][j]);
        puts("");
    }
    puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}
int finalMatch(int N)
{
    int i,ret=0,theta;
    minRowDel(N);
    minColDel(N);
    buildGraph(N);
    int found = findMatch((N<<1)+1);
    findTicks(N);
    while(found != N)
    {
        theta = findTheta(N);
        adjTheta(N, theta);
        buildGraph(N);
        found = findMatch((N<<1)+1);
        findTicks(N);
    }
    for (i=0; i<N; ++i) ret += original[i][MatchRow[i]];
    return ret;
}
int maxMatch(int N)
{
    int i,j,maxi=-1;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            if (original[i][j]>maxi) maxi = original[i][j];
        }
    }
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) matrix[i][j] = maxi - original[i][j];
    }
    return finalMatch(N);
}
int minMatch(int N)
{
    return finalMatch(N);
}
void takeInput(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            scanf("%d", &original[i][j]);
            matrix[i][j] = original[i][j];
        }
    }
}
int main()
{
    int N;
    while(scanf("%d", &N) != EOF)
    {
        takeInput(N);
        printf("%d\n", maxMatch(N));
    }
    return 0;
}
