#include<stdio.h>
#include<vector>
#include<stack>
#include<algorithm>
#define MAX 5003
using namespace std;
vector < vector <int> > VC(MAX);
stack <int> S;
int visited[MAX], index[MAX], lowlink[MAX];
int V,E;
int indx;
int out[MAX],oo;
void SCC(int node)
{
    int i,y;
    index[node] = lowlink[node] = indx;
    ++indx;
    S.push(node);
    for (i=0; i<VC[node].size(); ++i)
    {
        y = VC[node][i];
        if (index[y]==-1)
        {
            SCC(y);
            if (lowlink[y]<lowlink[node]) lowlink[node] = lowlink[y];
        }
        else if (index[y]<lowlink[node]) lowlink[node] = index[y];
    }
    if (lowlink[node] == index[node])
    {
        oo = 0;
        out[0] = S.top();
        ++oo;
        S.pop();
        while(out[oo-1]!=node)
        {
            out[oo++] = S.top();
            S.pop();
        }
        sort(out, out+oo);
        if (oo>1 || !VC[node].size())
        {
            printf("%d",out[0]);
            for (y=1; y<oo; ++y) printf(" %d",out[y]);
            puts("");
        }
    }
}
int main()
{
    //freopen("data.txt","r",stdin);
    //freopen("A.txt","w",stdout);
	int i,j,x,y;
	while(scanf("%d",&V) && V)
	{
		scanf("%d",&E);
		for (i=1; i<=V; ++i)
		{
		    VC[i].clear();
		    index[i] = lowlink[i] = -1;
		}
		for (i=1; i<=E; ++i)
		{
			scanf("%d%d",&x,&y);
			VC[x].push_back(y);
		}
		while(!S.empty()) S.pop();
		indx = 0;
		for (i=1; i<=V; ++i)
		{
		    if (index[i]==-1) SCC(i);
		}
	}
	return 0;
}
