#include<bits/stdc++.h>
using namespace std;
#define MAXN 40006
vector < int > V[MAXN];
list < int > ans;
int nmp, mp[206][206];
vector < pair < char , char > > rmp;
int in[MAXN], out[MAXN], enode[MAXN];
void euler_path(int node, list < int > :: iterator itl)
{
    int i,now;
    for(i=enode[node]; i<V[node].size(); i=enode[node])
    {
        now = V[node][i];
        ++enode[node];
        --in[now];
        euler_path(V[node][i], ans.insert(itl, now));
    }
}
int findidx(char ch1, char ch2)
{
    if (mp[ch1][ch2] == -1)
    {
        mp[ch1][ch2] = ++nmp;
        rmp.push_back(make_pair(ch1,ch2));
        V[nmp].clear();
        in[nmp] = out[nmp] = 0;
    }
    return mp[ch1][ch2];
}
int main()
{
    int N,i;
    char str[6];
    int x,y,start;
    int oddin, oddout;
    list < int > :: iterator itl;
    while (scanf("%d", &N) != EOF)
    {
        memset(mp, -1, sizeof(mp));
        rmp.clear(); rmp.push_back(make_pair(0,0));
        nmp = 0;
        for (i=1; i<=N; ++i)
        {
            scanf("%s", str);
            x = findidx(str[0],str[1]), y = findidx(str[1],str[2]);
            ++out[x], ++in[y];
            V[x].push_back(y);
        }
        oddin = oddout = 0;
        for (i=1; i<rmp.size(); ++i)
        {
            if (in[i] == out[i]) continue;
            if (abs(in[i]-out[i]) > 1) break;
            if (in[i] > out[i]) ++oddin;
            else ++oddout;
        }
        if (i<rmp.size() || oddin > 1 || oddout > 1)
        {
            puts("NO");
            continue;
        }
        start = 1;
        for (i=1; i<rmp.size(); ++i)
        {
            if (out[i] > in[i])
            {
                start = i;
                break;
            }
        }
        memset(enode, 0, sizeof(enode));
        ans.clear();
        euler_path(start,ans.begin());
        if (ans.size() != N)
        {
            puts("NO");
            continue;
        }
        puts("YES");
        printf("%c%c", rmp[start].first, rmp[start].second);
        for (itl = ans.end(); itl != ans.begin(); )
        {
            --itl;
            putchar(rmp[*itl].second);
        }
        puts("");
    }
}
