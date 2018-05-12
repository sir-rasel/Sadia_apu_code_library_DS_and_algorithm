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
using namespace std;               //REMEMBER TO TAKE DOUBLE SIZED ARRAY
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
    int sz, last;
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
        ++sz;
    }
    int size() {return sz;}
    void extend(char ch, int idx = -1)
    {
        int p, q, clone, cur = sz++;
        fnl = cur;
        init(cur);
        SA[cur].len = SA[last].len + 1;
        FirstPos[cur] = idx;
        NumOcc[cur] = 1;
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
                NumOcc[clone] = 0;
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
        sort(lenState.begin(), lenState.end());
        for (i=lenState.size()-1; i>=0; --i)
        {
            q = lenState[i].second;
            p = SA[q].link;
            if (p<1) continue;
            NumOcc[p] += NumOcc[q];
        }
    }
};
/*
dhori, SuffixAutomata sa;
sa.extend(character, index in string) diye automata te character jog kora jabe
shob char jog kora shesh hole, sa.distSubs() call korle return korbe number of substrings (distinct)
shob char jog kora shesh hole, sa.numOcc() call korle, prottekta state er respect e, oi state ta kotobar string e occur kore sheita NumOcc[state] e saved hobe
    jamon , abcbcabc er jonno, NumOcc["abc"] = 2, NumOcc["bc"] = NumOcc["c"] = 3 etc
    **string diye obosshoi access kora jabe nah, oita bujha'r shubidha'r jonno :)
extend kora'r shomoy index jodi pass kora hoy, tahole FirstPos[state] diye oi state ta prothom je position e occur kore sheita paowa jabe, SA[state].len diye oi state er length o paowa jabe
    jodi FirstPos er jaygay LastPos lage, then obviously string ta ulta kore automata te save korlei hobe, and len - n + 1 type calculation :)
traverse(string) diye traverse kora jabe, private traverse function er bhitre print e details ache :)

*/
int main()
{
    int i;
    while(scanf("%s", str) != EOF)
    {
        SuffixAutomata temp;
        printf("%d\n", temp.size());
        for (i=0; str[i]; ++i)
        {
            temp.extend(str[i], i); // index deyata optional, substring er first occurance lagle eikhane index pass korte hobe for each entry
            printf("%d\n", temp.size());
        }
        printf("%d\n", temp.size());
    }
    return 0;
}
