/*
 * Algoritm : Min Cost Max Flow using Bellmen Ford
 * Note : Vertex are 0 indexing Based
 */
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
using namespace std;
#define MAX_V 3777
#define INF 777777777
struct NODE{
	int v,Cap,Cost,RevInd;// This ind is necesery for multigraph to knw which edge is used to take flow
};
vector<NODE> Edge[ MAX_V+7];
int nV,nE,P;
int SRC,TNK;
// This PInd is neceserry for multigraph to knw which edge ind of parent is used to take flow
int Par[ MAX_V+7],PInd[MAX_V+7];
int SD[MAX_V+7];// Shortest path

void SetEdge( int u,int v,int Cap,int Cost )
{
	NODE U ={ v,Cap,Cost,Edge[v].size()};
	NODE V ={ u,0,-Cost,Edge[u].size()};
	Edge[u].push_back( U);
	Edge[v].push_back( V);
}
/*
bool BFord( void)
{
	int i,u,k;
	for( i=0;i<nV;i++){
		Par[i] =-1;SD[i] =INF;
	}
	bool IsChange =true;
	SD[SRC] =0;
	while( IsChange ){
		IsChange =false;
		for( u=SRC;u<=TNK;u++){
			for( i=0;i<Edge[u].size();i++){
				if( !Edge[u][i].Cap) continue;
				int v = Edge[u][i].v;
				TD = SD[u] +Edge[u][i].Cost;
				// relaxation
				if( SD[v] > TD ){
					SD[v] = TD;Par[v] =u;PInd[v] =i;
					IsChange =true;
				}
			}
		}
	}
	return Par[TNK]!=-1;
}
*/

bool dijk()
{
    int i,k;
	for( i=0;i<nV;i++){
		Par[i] =-1;SD[i] =INF;
	}

	#define pii pair<int,int>

	priority_queue< pii >pq;
	SD[SRC]=0;
    pii u,v;

    u.first=SRC;
    u.second=0;

    pq.push( u );


	while(!pq.empty())
    {
        u=pq.top();
        pq.pop();


        for( int i=0;i<(int)Edge[ u.second ].size();i++ )
        {

            if( !Edge[u.second][i].Cap) continue;

            v.second=Edge[u.second][i].v;
            v.first=u.first-Edge[u.second][i].Cost;

            if( SD[ v.second ]>-v.first )
            {
                SD[ v.second ]=-v.first;
                Par[ v.second ]=u.second;
                PInd[ v.second ] =i;
                pq.push( v );
            }

        }

    }

    return Par[TNK]!=-1;

}

int FindVol( int s,int t)
{
	int Cap =Edge[ Par[t]][ PInd[t]].Cap;
	if( s==Par[t]) return Cap;
	else return min( Cap,FindVol( s,Par[t]));
}

int AugmentPath( int s,int t,int V)
{
	if( s==t ) return 0;
	int Cost =Edge[ Par[t]][PInd[t]].Cost*V;
	Edge[ Par[t]][ PInd[t]].Cap -=V;
	Edge[ t][ Edge[ Par[t]][PInd[t]].RevInd].Cap +=V;
	return Cost + AugmentPath( s,Par[t],V);
}

int MinCost( )
{
    int Flow,Cost;
	Flow = Cost = 0;
	while( dijk()){

		int V =FindVol( SRC,TNK );
		Flow +=V;
		Cost +=AugmentPath( SRC,TNK,V);
        if(Flow==2)return Cost;
	}
}


int n,m;

int main()
{
   // freopen("in.txt","r",stdin);

    int i,j,k,u,v,a,b,ks=0;

    while(scanf("%d%d",&n,&m)==2)
    {
        //init(0,n-1,n);
        for( i=0;i<m;i++ )
        {
            scanf("%d%d%d%d",&u,&v,&a,&b);u--,v--;
            SetEdge(u,v,1,a);
            SetEdge(u,v,1,a+b);
        }
        SRC=0;
        TNK=n-1;
        nV=n;
        nE=2*m;

        printf("Case %d: %d\n",++ks,MinCost() );

        for( i=0;i<nV;i++ )Edge[i].clear();


    }
    return 0;
}

