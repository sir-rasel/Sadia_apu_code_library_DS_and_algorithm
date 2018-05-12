#pragma comment(linker, "/STACK:96777216")
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<iostream>
#include<assert.h>
using namespace std;
#define INF 1000000009
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MAXN 50006
#define MAXLOG 26
struct ttm
{
    int mn,mx;
    ttm () {}
    ttm (int _mn, int _mx) {mn = _mn, mx = _mx;}
} TREEm[4*MAXN];
int TREE1[4*MAXN], TREE2[4*MAXN], lazy[4*MAXN];
struct chain
{
    int ofst, sz, lvl, st;
} ChainInfo[MAXN];
int Parent[MAXN], Level[MAXN], SubSize[MAXN], HeavyChild[MAXN], ChainID[MAXN], NChain;
vector < int > Edges[MAXN];
int LG, LCA[MAXN][MAXLOG];
vector < int > ChainElem[MAXN];
int Cost[MAXN];
struct qq
{
    int ord;
    int cid, left, right;
    qq (int _ord, int _cid, int _left, int _right) {ord = _ord, cid = _cid, left = _left, right = _right;}
};
void init(int N)
{
    int i;
    for (i=1; i<=N; ++i)
    {
        Edges[i].clear();
        HeavyChild[i] = -1;
        ChainElem[i].clear();
        ChainElem[i].push_back(-1);
    }
    NChain = 0;
}
void dfs(int par, int node, int lvl)
{
    SubSize[node] = 1, Parent[node] = par, Level[node] = lvl;
    int now,i, msb = -1;
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i];
        if (now == par) continue;
        dfs(node, now, lvl+1);
        SubSize[node] += SubSize[now];
        if (msb == -1 || SubSize[msb] < SubSize[now]) msb = now;
    }
    if (msb != -1) HeavyChild[node] = msb;
}
void assign(int node, int cid)
{
    ChainID[node] = cid, ChainElem[cid].push_back(node);
    if (ChainInfo[cid].sz == 0) ChainInfo[cid].lvl = Level[node], ChainInfo[cid].st = node;
    ++ChainInfo[cid].sz;
    int now,i, par = Parent[node];
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i];
        if (now == par) continue;
        if (now == HeavyChild[node]) assign(now,cid);
        else
        {
            ++NChain;
            ChainInfo[NChain].sz = 0;
            assign(now,NChain);
        }
    }
}
void buildLCA(int N)
{
    int i,j, maxlevel = -1;
    for (i=1; i<=N; ++i)
    {
        if (Level[i] > maxlevel) maxlevel = Level[i];
    }
    for (LG=0; (1<<LG) <= maxlevel; ++LG);
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
    if (Level[u] < Level[v]) swap(u,v);
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
int t_init(int ofst, int cid, int node, int left, int right)
{
    lazy[ofst+node] = 0;
    if (left == right)
    {
        int c = Cost[ChainElem[cid][left]];
        TREEm[ofst+node] = ttm(c,c);
        TREE1[ofst+node] = TREE2[ofst+node] = 0;
        return ofst+node;
    }
    int mid = (left + right) / 2;
    int l = t_init(ofst, cid, 2*node, left, mid);
    int r = t_init(ofst, cid, 2*node+1, mid+1, right);
    int mn = MINI(TREEm[ofst+2*node].mn, TREEm[ofst+2*node+1].mn);
    int mx = MAXI(TREEm[ofst+2*node].mx, TREEm[ofst+2*node+1].mx);
    TREEm[ofst+node] = ttm(mn,mx);
    TREE1[ofst+node] = MAXI(TREE1[ofst+2*node], TREE1[ofst+2*node+1]);
    TREE1[ofst+node] = MAXI(TREE1[ofst+node], TREEm[ofst+2*node+1].mx - TREEm[ofst+2*node].mn);
    TREE2[ofst+node] = MAXI(TREE2[ofst+2*node], TREE2[ofst+2*node+1]);
    TREE2[ofst+node] = MAXI(TREE2[ofst+node], TREEm[ofst+2*node].mx - TREEm[ofst+2*node+1].mn);
    return MAXI(l,r);
}
void updatelazy(int ofst, int node, int left, int right)
{
    if (left == right)
    {
        lazy[ofst+node] = 0;
        return;
    }
    int val = lazy[ofst+node];
    lazy[ofst+node] = 0;
    lazy[ofst+2*node] += val, lazy[ofst+2*node+1] += val;
    TREEm[ofst+2*node].mn += val, TREEm[ofst+2*node].mx += val;
    TREEm[ofst+2*node+1].mn += val, TREEm[ofst+2*node+1].mx += val;
}
void update(int ofst, int node, int left, int right, int start, int end, int val)
{
    if (end < left || right < start) return;
    if (start <= left && right <= end)
    {
        lazy[ofst+node] += val;
        TREEm[ofst+node].mn += val, TREEm[ofst+node].mx += val;
        return;
    }
    if (lazy[ofst+node]) updatelazy(ofst, node, left, right);
    int mid = (left + right) / 2;
    update(ofst, 2*node, left, mid, start, end, val);
    update(ofst, 2*node+1, mid+1, right, start, end, val);
    int mn = MINI(TREEm[ofst+2*node].mn, TREEm[ofst+2*node+1].mn);
    int mx = MAXI(TREEm[ofst+2*node].mx, TREEm[ofst+2*node+1].mx);
    TREEm[ofst+node] = ttm(mn,mx);
    TREE1[ofst+node] = MAXI(TREE1[ofst+2*node], TREE1[ofst+2*node+1]);
    TREE1[ofst+node] = MAXI(TREE1[ofst+node], TREEm[ofst+2*node+1].mx - TREEm[ofst+2*node].mn);
    TREE2[ofst+node] = MAXI(TREE2[ofst+2*node], TREE2[ofst+2*node+1]);
    TREE2[ofst+node] = MAXI(TREE2[ofst+node], TREEm[ofst+2*node].mx - TREEm[ofst+2*node+1].mn);
}
void update(int cid, int left, int right, int val)
{
    update(ChainInfo[cid].ofst, 1,1,ChainInfo[cid].sz, left, right, val);
}
void prep(int N)
{
    dfs(-1, 1, 1);
    ChainInfo[1].sz = 0;
    assign(1,++NChain);
    int ofst = 0, cid;
    for (cid=1; cid<=NChain; ++cid)
    {
        ChainInfo[cid].ofst = ofst;
        ofst = t_init(ofst, cid, 1,1,ChainInfo[cid].sz);
    }
    buildLCA(N);
}
int pos_in_chain(int node)
{
    int cid = ChainID[node];
    return Level[node] - ChainInfo[cid].lvl + 1;
}
#define pii pair < int , int >
#define mp make_pair
pair < pii , pii > query(int ofst, int node, int left, int right, int start, int end) /// < < mn,mx > , < ans1,ans2 > >
{
    if (end < left || right < start) return mp(mp(INF,-INF),mp(0,0));
    if (start <= left && right <= end) return mp(mp(TREEm[ofst+node].mn,TREEm[ofst+node].mx),mp(TREE1[ofst+node],TREE2[ofst+node]));
    if (lazy[ofst+node]) updatelazy(ofst, node,left,right);
    int mid = (left + right) / 2;
    pair < pii , pii > l = query(ofst, 2*node, left, mid, start, end);
    pair < pii , pii > r = query(ofst, 2*node+1, mid+1, right, start, end);
    pair < pii , pii > ret;
    ret.first.first = MINI(l.first.first, r.first.first);
    ret.first.second = MAXI(l.first.second, r.first.second);
    ret.second.first = MAXI(l.second.first, r.second.first);
    ret.second.first = MAXI(ret.second.first, r.first.second - l.first.first);
    ret.second.second = MAXI(l.second.second, r.second.second);
    ret.second.second = MAXI(ret.second.second, l.first.second - r.first.first);
    return ret;
}
pair < pii , pii > query(int cid, int left, int right)
{
    return query(ChainInfo[cid].ofst, 1, 1, ChainInfo[cid].sz, left, right);
}
void walk(int u, int v, vector < qq > &Q)
{
    int ucid, vcid, p;
    int f = 1;
    if (Level[u] > Level[v])
    {
        swap (u,v);
        f = 2;
    }
    ucid = ChainID[u], vcid = ChainID[v];
    while (vcid != ucid)
    {
        p = pos_in_chain(v);
        Q.push_back(qq(f,vcid,1,p));
        v = ChainInfo[vcid].st; v = Parent[v];
        vcid = ChainID[v];
    }
    Q.push_back(qq(f,ucid, pos_in_chain(u)+1, pos_in_chain(v)));
    if (Q.back().left > Q.back().right) Q.pop_back();
    if (f == 1) reverse(Q.begin(), Q.end());
}
int path(int u, int v, int c)
{
    int l = findLCA(u,v), q;
    vector < qq > Q, TQ;
    if (l == u)
    {
        Q.push_back(qq(1, ChainID[u], pos_in_chain(u), pos_in_chain(u)));
        walk(u,v,TQ);
        for (q=0; q<TQ.size(); ++q) Q.push_back(TQ[q]);
    }
    else if (l == v)
    {
        walk(u,v,Q);
        Q.push_back(qq(2, ChainID[v], pos_in_chain(v), pos_in_chain(v)));
    }
    else
    {
        walk(u,l,Q);
        Q.push_back(qq(2, ChainID[l], pos_in_chain(l), pos_in_chain(l)));
        walk(l,v,TQ);
        for (q=0; q<TQ.size(); ++q) Q.push_back(TQ[q]);
    }
    int ret = 0, mn = INF;
    pair < pii , pii > nq;
    for (q=0; q<Q.size(); ++q)
    {
        //printf("%d %d %d %d\n", Q[q].ord, Q[q].cid, Q[q].left, Q[q].right);
        nq = query(Q[q].cid, Q[q].left, Q[q].right);
        if (Q[q].ord == 1) ret = MAXI(ret, nq.second.first);
        else ret = MAXI(ret, nq.second.second);
        ret = MAXI(ret, nq.first.second - mn);
        mn = MINI(mn, nq.first.first);
        update(Q[q].cid, Q[q].left, Q[q].right, c);
    }
    return ret;
}
void print(int N)
{
    int node,cid,n;
    for (cid=1; cid<=NChain; ++cid)
    {
        node = n = ChainInfo[cid].st;
        printf("Chain %d (%d) ((%d)):", cid, ChainInfo[cid].sz, ChainInfo[cid].ofst);
        while (n != -1)
        {
            printf(" %d", n);
            n = HeavyChild[n];
        }
        puts("");
    }
}
int main()
{
    int T,N,Q,x,y,v,i;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (i=1; i<=N; ++i) scanf("%d", &Cost[i]);
        init(N);
        for (i=2; i<=N; ++i)
        {
            scanf("%d %d", &x, &y);
            Edges[x].push_back(y);
            Edges[y].push_back(x);
        }
        prep(N);
        //print(N);
        scanf("%d", &Q);
        while (Q--)
        {
            scanf("%d %d %d", &x, &y, &v);
            printf("%d\n", path(x,y,v));
        }
    }
    return 0;
}
/*
16
1 2
1 5
2 3
2 4
5 6
5 7
4 9
4 8
8 10
10 12
12 13
12 14
6 11
11 15
11 16
*/


/*
1
6
1 3 2 5 6 4
1 3
1 2
2 5
2 4
5 6
6
4 3 2
1 4 1
3 4 5
4 6 1
3 6 3
6 3 1
*/
