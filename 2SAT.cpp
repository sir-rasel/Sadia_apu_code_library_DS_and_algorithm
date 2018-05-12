//2SAT
#include<stdio.h>
#include<string.h>
#include<vector>
#include<stack>
#include<utility>
#include<algorithm>
using namespace std;
#define MAXN 8000
vector < vector < int > > V(2*MAXN+6);
vector < vector < int > > VR(2*MAXN+6);
int fin[2*MAXN+6];
bool vis[2*MAXN+6];
stack <int> finish;
int scc[2*MAXN+6];
int truth[2*MAXN+6];
bool cmp(int x, int y)
{
    return scc[x] > scc[y];
}
int val(int x)
{
    if (x<0) return 2*(-x) + 1;
    return 2*x;
}
int cmt(int x)
{
    if (x<0) return -2*x;
    return 2*x + 1;
}
void dfs(int node)
{
    vis[node] = true;
    int i;
    for (i=0; i<V[node].size(); ++i)
    {
        if (!vis[V[node][i]]) dfs(V[node][i]);
    }
    finish.push(node);
}
void dfs2(int node, int c)
{
    vis[node] = true;
    scc[node] = c;
    int i;
    for (i=0; i<VR[node].size(); ++i)
    {
        if (!vis[VR[node][i]]) dfs2(VR[node][i],c);
    }
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int t,T;
    int M,N;
    int i,c,x,y;
    bool f;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d %d", &M, &N);
        for (i=2; i<=2*N+1; ++i) V[i].clear(), VR[i].clear();
        while(M--)
        {
            scanf("%d %d", &x, &y);
            V[cmt(x)].push_back(val(y));
            V[cmt(y)].push_back(val(x));
            VR[val(y)].push_back(cmt(x));
            VR[val(x)].push_back(cmt(y));
        }
        memset(vis, false, sizeof(vis));
        while(!finish.empty()) finish.pop();
        for (i=2; i<=2*N+1; ++i)
        {
            if (!vis[i]) dfs(i);
        }
        c = 1;
        memset(vis, false, sizeof(vis));
        while(!finish.empty())
        {
            i = finish.top();
            finish.pop();
            if (!vis[i])
            {
                dfs2(i,c);
                ++c;
            }
        }
        f = true;
        for (i=1; f && i<=N; ++i)
        {
            if (scc[2*i]==scc[2*i+1]) f = false;
        }
        printf("Case %d: %s\n", t, f ? "Yes":"No");
        if (!f) continue;
        for (i=0; i<2*N; ++i) fin[i] = i+2;
        sort(fin, fin+2*N, cmp);
        memset(truth, -1, sizeof(truth));
        for (i=0; i<2*N; ++i)
        {
            if (truth[fin[i]]==-1)
            {
                truth[fin[i]] = 1;
                truth[fin[i]%2?fin[i]-1:fin[i]+1] = 0;
            }
        }
        c = 0;
        for (i=1; i<=N; ++i)
        {
            if (truth[2*i]==1) ++c;
        }
        printf("%d", c);
        for (i=1; i<=N; ++i)
        {
            if (truth[2*i]==1) printf(" %d", i);
        }
        puts("");
    }
    return 0;
}
