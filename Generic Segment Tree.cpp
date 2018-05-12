/*please write code for segment tree on your own, use this one only to understand the concept & for learning purpose*/

#define MAX 100010

struct X
{
     int sum ;
     int lazy ;
} ;

X tree[4*MAX] ;
int in[MAX] ;
X ans ;
int x,y,val ;

void propagate(X &p, X &u, X &v)
{
    u.lazy += p.lazy ;
    v.lazy += p.lazy ;
}

void calculate(X &p, int len)
{
    p.sum = p.sum + p.lazy*len ;
}

void merge(X &p, X &u, X &v)
{
    p.sum = u.sum + v.sum ;
}

void lazyupdate(X &p)
{
    p.lazy += val ;
}

void lazyreset(X &p)
{
    p.lazy = 0 ;
}

void update(int b, int e, int node)
{
    int m = (b+e)>>1 ;
    int u = node<<1 ;
    int v = u+1 ;

    if(b>y || e<x)
    {
        calculate(tree[node],e-b+1) ;
        if(b != e)  propagate(tree[node],tree[u],tree[v]) ;
        lazyreset(tree[node]) ;

        return ;
    }

    if(b>=x && e<=y)
    {
        lazyupdate(tree[node]) ;

        calculate(tree[node],e-b+1) ;
        if(b != e)  propagate(tree[node],tree[u],tree[v]) ;
        lazyreset(tree[node]) ;

        return ;
    }

    propagate(tree[node],tree[u],tree[v]) ;
    lazyreset(tree[node]) ;

    update(b,m,u) ;
    update(m+1,e,v) ;

    merge(tree[node],tree[u],tree[v]) ;
}

void query(int b, int e, int node)
{
    int m = (b+e)>>1 ;
    int u = node<<1 ;
    int v = u+1 ;

    if(b>y || e<x)
    {
        calculate(tree[node],e-b+1) ;
        if(b != e)  propagate(tree[node],tree[u],tree[v]) ;
        lazyreset(tree[node]) ;

        return ;
    }

    if(b>=x && e<=y)
    {
        calculate(tree[node],e-b+1) ;
        if(b != e)  propagate(tree[node],tree[u],tree[v]) ;
        lazyreset(tree[node]) ;

        merge(ans,ans,tree[node]) ;

        return ;
    }

    propagate(tree[node],tree[u],tree[v]) ;
    lazyreset(tree[node]) ;

    query(b,m,u) ;
    query(m+1,e,v) ;

    merge(tree[node],tree[u],tree[v]) ;
}

void init(int b, int e, int node)
{
    lazyreset(tree[node]) ;

    if(b==e)
    {
        tree[node].sum = in[b] ;

        return ;
    }

    int m = (b+e)>>1 ;
    int u = node<<1 ;
    int v = u+1 ;

    init(b,m,u) ;
    init(m+1,e,v) ;

    merge(tree[node],tree[u],tree[v]) ;
}
