/*
 *    Minimum cost Arborescene
 *    Algorithm : Chu-liu-edmonds algorithm
 *    Order: O( V*E )
 *    Note: root must be in vertex 0
*/

#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_V 1007
#define pb push_back

struct EDGE{
    long v,c;
    bool InTr;
    EDGE( long v,long c,bool InTr = false )
    {
        this->v = v;
        this->c = c;
        this->InTr = InTr;
    }
};
typedef vector<EDGE> VE;

long nV,nE;                 // number of vertices and edges in initial
long Visit[MAX_V+7],TRUE;   // used in dfs to check for visit
bool InStk[MAX_V+7];        // used in dfs to check visted vertices is in recursive call
long Par[MAX_V+7];          // parent vertices in dfs
long TotV;                  // to count number of vertices in dfs call
long nG;                    // number of grp
long Grp[MAX_V+7];          // grp in dex oa vertice used in cycle contraction in DMST
/* to set all the vertices in a cycle in same grp */
void SetGrp( long u,long v,long n )
{
    Grp[v] = n;
    if( u==v ) return;
    SetGrp( u,Par[v],n );
}
/* dfs to to check in graph */
void Dfs( vector< VE > &Edge , long u , bool ChkTr = true )
{
    Visit[u] = TRUE;
    InStk[u] = true;
    TotV++;
    if( u==0 ) Grp[u] = nG++;
    else Grp[u] = -1;
    long i;
    for( i=0;i<Edge[u].size();i++){
        long v = Edge[u][i].v;
        if( ChkTr && Edge[u][i].InTr == false ) continue;
        if( InStk[v] ) SetGrp( v,u,nG++ );
        else if( Visit[v]!=TRUE ){
            Par[v] = u;
            Dfs( Edge,v,ChkTr );
        }
    }
    if( Grp[u]==-1 ) Grp[u] = nG++;
    InStk[u] = false;
}
/* this return cost of DMST
   should be call if arborescne
   is possible */
long DMST( vector< VE > &Edge )
{
    long N = Edge.size();
    vector<long> MU( N,-1 );
    vector<long> MI( N );
    long u,v,i,MinCost = 0;
    for( u=0;u<N;u++){
        for( i=0;i<Edge[u].size();i++){
            v = Edge[u][i].v;
            if( v==0 ) continue;
            if( MU[v]==-1 || Edge[ MU[v] ][ MI[v] ].c > Edge[u][i].c ){
                if( MU[v]!=-1 ){
                    MinCost -= Edge[ MU[v] ][ MI[v] ].c;
                    Edge[ MU[v] ][ MI[v] ].InTr = false;
                }
                MU[v] = u;
                MI[v] = i;
                MinCost += Edge[u][i].c;
                Edge[u][i].InTr = true;
            }
        }
    }
    /* termination condition */
    if( N==2 ) return Edge[ MU[1] ][ MI[1] ].c;

    TotV = 0;
    nG = 0;
    TRUE++;
    Dfs( Edge,0 );
    /* to check is any cycle created
       if all vertice can be reachable
       from root 0
    */
    if( TotV==N ) return MinCost;
    for( i=0;i<N;i++){
        if( Visit[i]==TRUE ) continue;
        Dfs( Edge,i );
    }
    /* new compressed graph is creating  */
    vector< VE > TmpE( nG );
    for( u=0;u<N;u++){
        for( i=0;i<Edge[u].size();i++){
            long v = Edge[u][i].v;
            if( v==0 ) continue;
            if( Grp[u]==Grp[v] ) continue;
            TmpE[ Grp[u]].pb( EDGE( Grp[v] , Edge[u][i].c - Edge[ MU[v] ][ MI[v] ].c ) );
        }
    }
    Edge.clear();
    return MinCost + DMST( TmpE );
}
int main( void )
{
    long i,u,v,c,Icase,k = 0;
    scanf("%ld%ld",&nV,&nE );
    vector< VE > Edge( nV );
    for( i=1;i<=nE;i++){
        scanf("%ld%ld%ld",&u,&v,&c );
        Edge[u].pb( EDGE( v,c ) );
    }
    /* initial check for is arborescence is possible */
    TotV = 0;
    TRUE++;
    Dfs( Edge,0,false );
    if( TotV!=nV ) printf("No arborescene\n",++k );
    printf("%ld\n",DMST( Edge ) );
    return 0;
}
