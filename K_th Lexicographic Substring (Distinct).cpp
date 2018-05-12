#include<stdio.h>
#include<iostream>
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
#define MAXLEN 90006
struct State
{
    int len, link;
    map < char , int > nxtc;
} SA[2*MAXLEN];
int DistSub[2*MAXLEN];
bool vis[2*MAXLEN];
char str[MAXLEN];
vector < pair < int , int > > lenState;
string ans;
class SuffixAutomata
{
    int sz, last;
    void init(int idx)
    {
        SA[idx].len = 0, SA[idx].link = -1;
        SA[idx].nxtc.clear();
    }
    int distSubs(int cur)
    {
        if (vis[cur]) return DistSub[cur];
        vis[cur] = true;
        if (cur) DistSub[cur] = 1;
        else DistSub[cur] = 0;
        map < char , int > :: iterator im;
        map < char , int > &M = SA[cur].nxtc;
        for (im = M.begin(); im != M.end(); ++im) DistSub[cur] += distSubs(im->second);
        return DistSub[cur];
    }
public:
    SuffixAutomata()
    {
        sz = last = 0;
        init(0);
        lenState.clear();
        ++sz;
    }
    void extend(char ch)
    {
        int p, q, clone, cur = sz++;
        init(cur);
        SA[cur].len = SA[last].len + 1;
        lenState.push_back(make_pair(SA[cur].len, cur));
        for (p = last; p != -1 && SA[p].nxtc.count(ch) == 0; p = SA[p].link) SA[p].nxtc[ch] = cur;
        if (p == -1) SA[cur].link = 0;
        else
        {
            q = SA[p].nxtc[ch];
            if (SA[p].len + 1 == SA[q].len) SA[cur].link = q;
            else
            {
                clone = sz++;
                init(clone);
                SA[clone] = SA[q];
                SA[clone].len = SA[p].len + 1;
                for (; p != -1 && SA[p].nxtc[ch] == q; p = SA[p].link) SA[p].nxtc[ch] = clone;
                SA[cur].link = SA[q].link = clone;
                lenState.push_back(make_pair(SA[clone].len, clone));
            }
        }
        last = cur;
    }
    int distSubs()
    {
        int i;
        memset(vis, false, sizeof(vis));
        sort(lenState.begin(), lenState.end());
        for (i=lenState.size()-1; i>=0; --i) distSubs(lenState[i].second);
        return distSubs(0);
    }
    void calc(int K)
    {
        int cur = 0;
        char ch;
        int p;
        while(K)
        {
            map < char , int > &M = SA[cur].nxtc;
            map < char , int > :: iterator im;
            for (im = M.begin(); im != M.end(); ++im)
            {
                ch = im -> first;
                p = im -> second;
                if (DistSub[p] < K) K -= DistSub[p];
                else
                {
                    putchar(ch);
                    --K;
                    cur = p;
                    break;
                }
            }
        }
    }
};
int main()
{
    freopen("data.txt", "w", stdout);
    int Q,K,i,maxK;
    for (i=0; i<MAXLEN; ++i) str[i] = i%26 + 'a';
    Q = 500;
    //while(scanf("%s %d", str, &Q) != EOF)
    {
        SuffixAutomata sa;
        for (i=0; str[i]; ++i) sa.extend(str[i]);
        maxK = sa.distSubs();
        while(Q--)
        {
            //printf("%d\n", Q);
            //scanf("%d", &K);
            K = maxK;
            if (K <= maxK) sa.calc(K);
            else printf("-1");
            puts("");
        }
    }
    return 0;
}
