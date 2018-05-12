// Modular Gauss
#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
#define SIZE 100
#define MOD 1000000007
long long matrix[SIZE+6][SIZE+6],P;
bool vis[SIZE+6], freevar[SIZE+6];
vector < vector < int > > V(SIZE+6);
long long bigmod(long long a, long long K, long long P)
{
    if (K==0) return 1;
    if (K%2) return (a*bigmod(a,K-1,P))%P;
    long long ret = bigmod(a,K/2,P);
    return (ret*ret)%P;
}
int findRow(int N, int r, int c)
{
    int j = r;
    while(j<=N)
    {
        if (matrix[j][c]) return j;
        ++j;
    }
    return -1;
}
void swap(int N, int r1, int r2)
{
    if (r1==r2) return;
    long long temp;
    int j;
    for (j=1; j<=N+1; ++j)
    {
        temp = matrix[r1][j];
        matrix[r1][j] = matrix[r2][j];
        matrix[r2][j] = temp;
    }
}
void GaussianElimination(int N)
{
    int i,ii,j,k;
    memset(freevar, false, sizeof(freevar));
    for (i=1,ii=1; ii<=N; ++ii,++i)
    {
        j = findRow(N,i,ii);
        if (j==-1)
        {
            freevar[ii] = true;
            --i;
            continue;
        }
        swap(N,i,j);
        for (j=N+1; j>=i; --j) matrix[i][j] = (matrix[i][j] * bigmod(matrix[i][ii],P-2,P))%P;
        for (j=i+1; j<=N; ++j)
        {
            for (k=N+1; k>=ii; --k) matrix[j][k] = (matrix[j][k] - matrix[j][ii] * matrix[i][k] + P) % P;
        }
    }
}
int dfs(int node)
{
    if (vis[node]) return 0;
    vis[node] = true;
    int i,c=freevar[node];
    for (i=0; i<V[node].size(); ++i)
    {
        if (!vis[V[node][i]]) c += dfs(V[node][i]);
    }
    return c;
}
int main()
{
    int t,T;
    int N,M,x,y;
    long long ans;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d %d %d", &N, &M, &P);
        memset(matrix, 0, sizeof(matrix));
        for (x=1; x<=N; ++x) V[x].clear();
        while(M--)
        {
            scanf("%d %d", &x, &y);
            matrix[x][y] = matrix[y][x] = 1;
            matrix[x][x] = matrix[y][y] = P-1;
            V[x].push_back(y);
            V[y].push_back(x);
        }
        GaussianElimination(N);
        memset(vis, false, sizeof(vis));
        ans = 1;
        for(x=1; x<=N; ++x)
        {
            if (!vis[x])
            {
                if (V[x].size()==0) continue;
                y = dfs(x);
                ans = (ans * bigmod(P,y,MOD))%MOD;
            }
        }
        printf("Case %d: %lld\n", t, ans);
    }
    return 0;
}
