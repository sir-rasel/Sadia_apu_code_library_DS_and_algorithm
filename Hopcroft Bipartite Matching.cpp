// Hopcroft Bipartite Matching
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
/*
matching (hopcroft-karp)
n: number of nodes on left side, nodes are numbered 1 to n
m: number of nodes on right side, nodes are numbered n+1 to n+m
G = 0[0] ? G1[G[1---n]] ? G2[G[n+1---n+m]]
*/
#define MAX 2006
#define INF 100006

vector < int > G[MAX];
bool visited[MAX];
char clr[MAX];
int ans[MAX];
int Left[MAX], Right[MAX], bmatch[MAX], dist[MAX];
int n,m ;

bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(bmatch[i]==0) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[0] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=0) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[bmatch[v]]==INF) {
                    dist[bmatch[v]] = dist[u] + 1;
                    Q.push(bmatch[v]);
                }
            }
        }
    }
    return (dist[0]!=INF);
}

bool dfs(int u) {
    int i, v, len;
    if(u!=0) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[bmatch[v]]==dist[u]+1) {
                if(dfs(bmatch[v])) {
                    bmatch[v] = u;
                    bmatch[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int bmatching = 0, i;
    memset(bmatch, 0, sizeof(bmatch));
    while(bfs())
        for(i=1; i<=n; i++)
            if(bmatch[i]==0 && dfs(i))
                bmatching++;
    return bmatching;
}

vector < int > in;
vector < int > out;

int main()
{
    int A,B,N,i,j,d;
    int x,y;
    scanf("%d %d %d", &A, &B, &N);
    in.clear(), out.clear();

    for (i=0; i<N; ++i)
    {
        scanf("%d %d", &x, &y);
        if (y==0) in.push_back(x);
        else out.push_back(x);
    }

    n = in.size(), m = out.size();

    for (i=0; i<in.size(); ++i)
    {
        for (j=0; j<out.size(); ++j)
        {
            if (in[i] > out[j]) continue;
            d = out[j] - in[i];
            if (d >= A || d <= B) G[i+1].push_back(n+j+1);
        }
    }

    hopcroft_karp();

    int s = 0;
    for (i=0; i<in.size(); ++i)
    {
        if (bmatch[i+1] != 0) ++s;
    }

    if (s == N/2)
    {
        puts("No reason");
        for (i=0; i<in.size(); ++i)
        {
            if (bmatch[i+1] != 0) printf("%d %d\n", in[i], out[bmatch[i+1]-1-n]);
        }
    }
    else puts("Liar");

    return 0;
}
