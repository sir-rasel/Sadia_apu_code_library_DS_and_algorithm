#include<stdio.h>
#include<string.h>
#include<vector>
#include<utility>
#include<stack>
#include<set>
using namespace std;
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MAXN 10006
stack < pair < int , int > > S;
vector < vector < int > > V(MAXN);
vector < vector < pair < int , int > > > BCC(MAXN);
vector < pair < int , int > > Bridge;
set < int > Artic;
int IdBCC[MAXN], DfsCounter, NumBCC;
struct
{
    int DfsNum, DfsLevel, NumChildren, Low;
    void init()
    {
        DfsNum = DfsLevel = -1;
        NumChildren = 0;
    }
} Prop[MAXN];
void extract(int node, int now)
{
    pair < int , int > pp,temp;
    ++NumBCC;
    pp = make_pair(node,now);
    while(S.top() != pp)
    {
        temp = S.top();
        S.pop();
        IdBCC[temp.first] = IdBCC[temp.second] = NumBCC;
        BCC[NumBCC].push_back(temp);
    }
    if (BCC[NumBCC].size()==0 || IdBCC[node] != IdBCC[now]) Bridge.push_back(S.top());
    else BCC[NumBCC].push_back(S.top());
    if (BCC[NumBCC].size()==0) --NumBCC;
    S.pop();
}
void dfs(int node)
{
    Prop[node].Low = Prop[node].DfsNum = ++DfsCounter;
    int i,now;
    for (i=0; i<V[node].size(); ++i)
    {
        now = V[node][i];
        if (Prop[now].DfsNum==-1)
        {
            Prop[now].DfsLevel = Prop[node].DfsLevel + 1;
            ++Prop[node].NumChildren;
            S.push(make_pair(node,now));
            dfs(now);
            Prop[node].Low = MINI(Prop[node].Low, Prop[now].Low);
            if (Prop[node].DfsNum==1)
            {
                if (Prop[node].NumChildren>=2) Artic.insert(node);
                extract(node, now);
            }
            else
            {
                if (Prop[now].Low >= Prop[node].DfsNum)
                {
                    Artic.insert(node);
                    extract(node, now);
                }
            }
        }
        else
        {
            if (Prop[now].DfsLevel < Prop[node].DfsLevel - 1)
            {
                Prop[node].Low = MINI(Prop[node].Low, Prop[now].DfsNum);
                S.push(make_pair(node, now));
            }
        }
    }
}
void printRes()
{
    printf("Articulation Points : ");
    set < int > :: iterator is;
    for (is = Artic.begin(); is != Artic.end(); ++is) printf("%d ", *is); puts("");
    printf("Bridges : %d\n", Bridge.size());
    int i;
    for (i=0; i<Bridge.size(); ++i) printf("%d %d\n", Bridge[i].first, Bridge[i].second);
    puts("");
}
void initialize(int N)
{
    int i;
    for (i=1; i<=N; ++i)
    {
        V[i].clear();
        BCC[i].clear();
        Prop[i].init();
    }
    while(!S.empty()) S.pop();
    Artic.clear();
    Bridge.clear();
    NumBCC = DfsCounter = 0;
    Prop[1].DfsLevel = 1;
}
void takeInput(int N, int E)
{
    int x,y;
    while(E--)
    {
        scanf("%d %d", &x, &y); ++x,++y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
}
int main()
{
    freopen("data.txt", "r", stdin);
    int N,E;
    while(scanf("%d %d", &N, &E) != EOF)
    {
        initialize(N);
        takeInput(N,E);
        dfs(1);
        printRes();
    }
    return 0;
}
