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
#define EPS 1e-15
#define MAXN 100006
#define BLUE 0
#define RED 1
vector < vector < pair < int , bool > > > Edges(MAXN);
double p2[MAXN];
double blue(double x)
{
    //printf("blue : %lf\n", x);
    int i;
    for (i=1; ; ++i)
    {
        if (x + i > 1) break;
    }
    return (x+i) / p2[i-1];
}
double red(double x)
{
    //printf("red : %lf\n", x);
    int i;
    for (i=1; ; ++i)
    {
        if (x-i < -1) break;
    }
    return (x-i) / p2[i-1];
}
double rec(int parent, int node)
{
    double ret = 0;
    int now,i,c;
    for (i=0; i<Edges[node].size(); ++i)
    {
        now = Edges[node][i].first, c = Edges[node][i].second;
        if (now == parent) continue;
        if (c == BLUE) ret += blue(rec(node,now));
        else ret += red(rec(node,now));
    }
    return ret;
}
int main()
{
    int T,N,i,x,y,c;
    double ans;
    p2[0] = 1;
    for (i=1; i<MAXN; ++i) p2[i] = p2[i-1] * 2;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (i=1; i<=N; ++i) Edges[i].clear();
        for (i=1; i<N; ++i)
        {
            scanf("%d %d %d", &x, &y, &c);
            Edges[x].push_back(make_pair(y,c));
            Edges[y].push_back(make_pair(x,c));
        }
        ans = rec(-1,1);
        if (ans > 0) printf("BLUE BLUE\n");
        else if (ans < 0) printf("RED RED\n");
        else printf("RED BLUE\n");
    }
    return 0;
}
