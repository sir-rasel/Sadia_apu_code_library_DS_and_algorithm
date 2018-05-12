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
#include<iostream>
#include<assert.h>
using namespace std;
#define ll long long
#define pii pair< int,int >

const int N=502;

int n,n1,n2,vst[N];
ll sx[2],sy[2],sx2[2],sy2[2],sz[2],x[N],y[N];
double dst[2];


void take( int i,int p )
{
    sx[ p ]+=x[i];
    sy[ p ]+=y[i];
    sx2[ p ]+=x[i]*x[i];
    sy2[ p ]+=y[i]*y[i];
    sz[ p ]++;
    vst[ i ]=1;
}

pair<int,int> find(int p)
{
    int i,j;
    ll mx=0,d;
    for( i=0;i<n;i++ )
    {
        if(vst[i])continue;
        d=sx2[ p ]+sy2[ p ]-2*x[i]*sx[ p ]-2*y[i]*sy[ p ]+ sz[ p ]*x[i]*x[i]+sz[ p ]*y[i]*y[i];
        if( d>mx ){d=mx,j=i;}
    }

    return make_pair( j,sqrt((double)d) );
}




int main()
{
    int i,j,k,p;

    while(scanf("%d",&n)==1)
    {
        n=2*n;
        for( i=0;i<n;i++ )
        {
            scanf("%d%d",&x[i],&y[i]);
        }

        double ans=0;

        for( i=0;i<n;i++ )
        {
            memset(vst,0,sizeof(vst));
            dst[0]=dst[1]=0;
            sz[ 0 ]=sz[ 1 ]=0;

            take( i,0 );
            k=find( 0 ).first;
            take( k,1 );

            for(j=0;j<n-2;j++)
            {
                p=j&1;
                pii u=find( p );
                take( u.first,p );
                dst[ p ]+=u.second;
            }

            ans=max( ans,dst[0]-dst[1] );

        }
        printf("%.3lf\n",ans);
    }

    return 0;
}
