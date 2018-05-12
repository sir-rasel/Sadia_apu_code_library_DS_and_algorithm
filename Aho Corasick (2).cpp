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
using namespace std;
#define MAXS 250006
#define MAXN 506
#define MAXL 1000006
#define MAXALPHA 26
char str[MAXL],pat[MAXN];
int TRIE[MAXS][MAXALPHA],trsz;
int ends[MAXN];
int acfail[MAXS];
int cnt[MAXS];
vector < int > VQ;
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
            cnt[trsz] = 0;
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
    VQ.clear();
    queue < int > Q;
    for (ch = 0; ch < 26; ++ch)
    {
        nxt = TRIE[0][ch];
        if (nxt == -1) continue;
        Q.push(nxt);
        VQ.push_back(nxt);
    }
    while (!Q.empty())
    {
        now = Q.front();
        Q.pop();
        for (ch = 0; ch < 26; ++ch)
        {
            nxt = TRIE[now][ch];
            if (nxt == -1) continue;
            f = acfail[now];
            while (f != 0 && TRIE[f][ch] == -1) f = acfail[f];
            if (TRIE[f][ch] != -1) f = TRIE[f][ch];
            acfail[nxt] = f;
            Q.push(nxt);
            VQ.push_back(nxt);
        }
    }
    reverse(VQ.begin(), VQ.end());
}
void actrav(char *s)
{
    int cur = 0,f;
    char ch;
    while (*s)
    {
        ch = *s - 'a';
        if (TRIE[cur][ch] == -1)
        {
            f = cur;
            while (f != 0 && TRIE[f][ch] == -1) f = acfail[f];
            if (TRIE[f][ch] != -1)
            {
                f = TRIE[f][ch];
                ++cnt[f];
            }
            cur = f;
        }
        else
        {
            cur = TRIE[cur][ch];
            ++cnt[cur];
        }
        ++s;
    }
}
void calc()
{
    int i,nxt,now;
    for (i=0; i<VQ.size(); ++i)
    {
        nxt = VQ[i];
        now = acfail[nxt];
        if (now) cnt[now] += cnt[nxt];
    }
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int t,T;
    int N,i;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        scanf("%s", str);
        memset(TRIE, -1, sizeof(TRIE));
        cnt[0] = trsz = 0;
        for (i=0; i<N; ++i)
        {
            scanf("%s", pat);
            trinsert(pat,i);
        }
        acprep();
        actrav(str);
        calc();
        printf("Case %d:\n", t);
        for (i=0; i<N; ++i) printf("%d\n", cnt[ends[i]]);
    }
    return 0;
}
