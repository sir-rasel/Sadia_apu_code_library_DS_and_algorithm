//heavy light decomposition
#include<stdio.h>
#include<string.h>
#include<vector>
#include<utility>
#include<stack>
using namespace std;
#define MAXN 10006
vector < vector < pair < int, int > > > Edges(MAXN);
vector < int > Heavy;
stack < int > Stk;
int HeavyChild[MAXN], Parent[MAXN], SubtreeSize[MAXN];
pair < int , int > ChainIndex[MAXN];
bool HeavyParent[MAXN];
int dfs(int node, int parent)
{
    Parent[node] = parent;
    if (Edges[node].size()==0) return SubtreeSize[node] = 1;
    int i, sz = 1, now;
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i].first;
        if (now != parent) sz += dfs(now, node);
    }
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i].first;
        if (now != parent && 2*SubtreeSize[now]>sz)
        {
            //printf("Heavy Edge : %d %d\n", node, now);
            Stk.push(node);
            HeavyChild[node] = now;
            HeavyParent[now] = true;
            break;
        }
    }
    return SubtreeSize[node] = sz;
}
void assignChain(int node, int chain, int idx)
{
    while(node != -1)
    {
        ChainIndex[node] = make_pair(chain,idx);
        node = HeavyChild[node];
        ++idx;
    }
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int N;
    int i,now;
    int x,y,c;
    int Nchain;
    while(!Stk.empty()) Stk.pop();
    while(scanf("%d", &N) != EOF)
    {
        for (i=1; i<=N; ++i) Edges[i].clear();
        for (i=1; i<N; ++i)
        {
            scanf("%d %d %d", &x, &y, &c);
            Edges[x].push_back(make_pair(y,c));
            Edges[y].push_back(make_pair(x,c));
        }
        memset(HeavyChild, -1, sizeof(HeavyChild));
        memset(HeavyParent, false, sizeof(HeavyParent));
        dfs(1,0);
        for (i=1; i<=N; ++i) ChainIndex[i].first = -1;
        Nchain = 0;
        while(!Stk.empty())
        {
            now = Stk.top();
            Stk.pop();
            if (ChainIndex[now].first == -1) assignChain(now, ++Nchain, 1);
        }
        //for (i=1; i<=N; ++i) printf("%d : %d %d\n", i, ChainIndex[i].first, ChainIndex[i].second);
    }
    return 0;
}
