// Suffix Automata
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
using namespace std;               ///REMEMBER TO TAKE DOUBLE SIZED ARRAY
#define MAXLEN 1000006
struct State
{
    int len, link;
    map < char , int > nxtc;
} SA[2*MAXLEN];
int FirstPos[2*MAXLEN], DistSub[2*MAXLEN], NumOcc[2*MAXLEN];
bool vis[2*MAXLEN];
char str[MAXLEN];
vector < pair < int , int > > lenState;
class SuffixAutomata
{
    int sz, last, lm;
    int fnl;
    void init(int idx)
    {
        SA[idx].len = 0, SA[idx].link = -1;
        FirstPos[idx] = -1;
        SA[idx].nxtc.clear();
    }
    bool traverse(int cur, char *ch)
    {
        if (*ch == 0)
        {
            printf("first occurance lasts at = %d :: total # of occurances = %d :: node = %d\nlink = %d :: len = %d\n", FirstPos[cur], NumOcc[cur], cur, SA[cur].link, SA[cur].len);
            return true;
        }
        if (SA[cur].nxtc.count(*ch) == 0) return false;
        int p = SA[cur].nxtc[*ch];
        return traverse(p, ++ch);
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
        lm = 0;
        ++sz;
    }
    int size() {return sz;}
    void extend(char ch, int idx = -1)
    {
        int p, q, clone, cur = sz++;
        lm = fnl = cur;
        init(cur);
        SA[cur].len = SA[last].len + 1;
        FirstPos[cur] = idx;
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
                FirstPos[clone] = FirstPos[q];
                lenState.push_back(make_pair(SA[clone].len, clone));
            }
        }
        last = cur;
    }
    void traverse(char *str)
    {
        if (traverse(0, str) == 0) puts("not a substring");
    }
    int distSubs()
    {
        int i;
        memset(vis, false, sizeof(vis));
        sort(lenState.begin(), lenState.end());
        for (i=lenState.size()-1; i>=0; --i) distSubs(lenState[i].second);
        return distSubs(0);
    }
    void numOcc()
    {
        int i,p,q;
        map < char, int > :: iterator im;
        memset(NumOcc, 0, sizeof(NumOcc));
        NumOcc[lm] = 1;
        sort(lenState.begin(), lenState.end());
        for (i=lenState.size()-1; i>=0; --i)
        {
            p = lenState[i].second;
            if (p < 1) continue;
            map < char , int > &M = SA[p].nxtc;
            for (im = M.begin(); im != M.end(); ++im)
            {
                q = im -> second;
                NumOcc[p] += NumOcc[q];
            }
        }
    }
};
int main()
{
    int i;
    while(scanf("%s", str) != EOF)
    {
        SuffixAutomata temp;
        for (i=0; str[i]; ++i)
        {
            temp.extend(str[i], i); // index deyata optional, substring er first occurance lagle eikhane index pass korte hobe for each entry
        }
        temp.extend('$');
        temp.numOcc();
        while(scanf("%s", str) != EOF) temp.traverse(str);
    }
    return 0;
}
