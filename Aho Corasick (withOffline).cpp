/// Aho Corasick Offline

#include<bits/stdc++.h>
using namespace std;
#define MAXS 1000006
#define MAXN 1000006
#define MAXL 1000006
#define MAXALPHA 26
char str[MAXL],pat[MAXL];
int TRIE[MAXS][MAXALPHA],trsz;
int ends[MAXN];
int acfail[MAXS];
int BIT[MAXS*2];
int st[MAXS], nd[MAXS], tm;
bool stat[MAXN];
vector < vector < int > > Edges(MAXN);
void update(int N, int idx, int val)
{
    if (idx == 0) return;
    while (idx <= N)
    {
        BIT[idx] += val;
        idx += idx & -idx;
    }
}
int query(int idx)
{
    int ret = 0;
    while (idx > 0)
    {
        ret += BIT[idx];
        idx -= idx & -idx;
    }
    return ret;
}
void trinsert(char *str, int idx)
{
    int cur = 0;
    char *s = str;
    char ch;
    while (*s)
    {
        ch = *s - 'a';
        if (TRIE[cur][ch] == -1)
        {
            ++trsz;
            TRIE[cur][ch] = trsz;
            stat[trsz] = 1;
        }
        cur = TRIE[cur][ch];
        ++s;
    }
    ends[idx] = cur;
}
void acprep()
{
    int ch,nxt,now,f;
    memset(acfail, 0, sizeof(acfail));
    queue < int > Q;
    for (ch = 0; ch < MAXALPHA; ++ch)
    {
        nxt = TRIE[0][ch];
        if (nxt == -1) continue;
        Edges[0].push_back(nxt);
        Q.push(nxt);
    }
    while (!Q.empty())
    {
        now = Q.front();
        Q.pop();
        for (ch = 0; ch < MAXALPHA; ++ch)
        {
            nxt = TRIE[now][ch];
            if (nxt == -1) continue;
            f = acfail[now];
            while (f != 0 && TRIE[f][ch] == -1) f = acfail[f];
            if (TRIE[f][ch] != -1) f = TRIE[f][ch];
            acfail[nxt] = f;
            Q.push(nxt);
            Edges[f].push_back(nxt);
        }
    }
}
void dfs(int node)
{
    ++tm;
    st[node] = tm;
    int i,now;
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i];
        dfs(now);
    }
    nd[node] = tm;
}
int actrav(char *s)
{
    int cur = 0,f;
    char ch;
    int ret = 0;
    while (*s)
    {
        ch = *s - 'a';
        if (TRIE[cur][ch] == -1)
        {
            f = cur;
            while (f != 0 && TRIE[f][ch] == -1) f = acfail[f];
            if (TRIE[f][ch] != -1) f = TRIE[f][ch];
            cur = f;
        }
        else cur = TRIE[cur][ch];
        ret += query(st[cur]);
        ++s;
    }
    return ret;
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int t,T;
    int Q,N,i,x,s,n;
    while (scanf("%d %d", &Q, &N) != EOF)
    {
        memset(TRIE, -1, sizeof(TRIE));
        memset(BIT, 0, sizeof(BIT));
        trsz = 0;
        for (i=1; i<=N; ++i)
        {
            scanf("%s", pat);
            trinsert(pat,i);
        }
        acprep();
        tm = -1;
        dfs(0);
        for (i=1; i<=N; ++i)
        {
            x = ends[i];
            s = st[x], n = nd[x];
            update(tm,s,1);
            update(tm,n+1,-1);
        }
        while (Q--)
        {
            scanf("%s", str);
            if (str[0] == '?')
            {
                printf("%d\n", actrav(str+1));
                continue;
            }
            sscanf(str+1, "%d", &x);
            x = ends[x];
            s = st[x], n = nd[x];
            if (str[0] == '+')
            {
                if (stat[x]) continue;
                update(tm,s,1);
                update(tm,n+1,-1);
                stat[x] = true;
            }
            else
            {
                if (!stat[x]) continue;
                update(tm,s,-1);
                update(tm,n+1,1);
                stat[x] = false;
            }
        }
        for (i=0; i<=trsz; ++i) Edges[i].clear();
    }
    return 0;
}
