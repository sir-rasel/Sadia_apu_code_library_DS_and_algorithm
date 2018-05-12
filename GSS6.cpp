#pragma warning(disable:4786)
#include<bits/stdc++.h>

using namespace std;

#define MEM(a,b) memset(a,(b),sizeof(a))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define inf 1000000001

typedef long  LL;

inline int MAX3(LL a,LL b,LL c) { return MAX(a,MAX(b,c));}

const int MAXN = 100100;

struct node
{
    node *l, *r;
    int pri,size;
    LL val,best,pref,suf,sum;

    void update()
	{
        size = l->size + 1 + r->size;
		sum  = l->sum + val+ r->sum;
		best= val+MAX3(l->suf,r->pref,l->suf+r->pref);
		best= MAX3(MAX(best,val),l->best,r->best);
		pref = MAX3(l->pref , l->sum+val, l->sum+val+r->pref);
		suf =  MAX3(r->suf  , r->sum+val, r->sum+val+l->suf );
    }
};

void print(int pos,node x)
{
	printf("pos=%d sz=%d val=%d best=%d prf=%d suf=%d sum=%d lsize=%d rsize=%d\n",pos,x.size,x.val,x.best,x.pref,x.suf,x.sum,x.l->size ,x.r->size);
}

struct treap
{
    node *root, *dummy;

    treap()
	{
        srand( 3209423 );
		node* alloc=new node();
        alloc->l = alloc->r = alloc;
        alloc->best = alloc->pref = alloc->suf = -inf;
        alloc->pri = -1;
        alloc->size=alloc->sum=alloc->val=0;
        root =  dummy = alloc ;
    }

    node *rotate( node *a, node *b )
	{
        if( a->l == b ) { a->l = b->r; b->r = a; }
        else { a->r = b->l; b->l = a; }
        a->update(); b->update();
        return b;
    }

    node *insert( node *x, int pos, int val )
	{
        if( x == dummy )
		{
			node* alloc=new node();
            alloc->l = alloc->r = dummy;
            alloc->best = alloc->sum=alloc->val= alloc->suf = alloc->pref = val;
            alloc->pri = rand();
            alloc->size = 1;
            return alloc;
        }

        if( x->l->size >= pos )
		{
            x->l = insert( x->l, pos, val );
            if( x->l->pri > x->pri ) x = rotate( x, x->l );
        }
        else
		{
            x->r = insert( x->r, pos - x->l->size - 1, val );
            if( x->r->pri > x->pri ) x = rotate( x, x->r );
        }

        x->update();
        return x;
    }

	node successor(node *x)
	{
		node *now=x;
		while(now->r!=dummy) now=now->r;
		return *now;
	}

	node predecessor (node *x)
	{
		node *now=x;
		while(now->l!=dummy) now=now->l;
		return *now;
	}

	node *erase( node *x, int pos)
	{

		if(x->l==dummy && x->r==dummy) return dummy;

        if( x->l->size==pos )
		{

			node tmp=*x;

			if(x->l==dummy || x->r==dummy)
			{
				if(x->l!=dummy) return x->l;
				else return x->r;
			}
			else
			{
				node y=successor(x->l);x->val=y.val;
				//printf("left %d\n",y.val);
				x->l=erase(x->l,x->l->size-1);
			}
        }
        else if( x->l->size >= pos + 1 )
		{
            x->l = erase( x->l, pos);
            if( x->l->pri > x->pri ) x = rotate( x, x->l );
        }
        else
		{
            x->r = erase( x->r, pos - x->l->size - 1);
            if( x->r->pri > x->pri ) x = rotate( x, x->r );
        }

        x->update();
	//	print(pos,*x);
        return x;
    }

	void replace( node *x, int pos,int val)
	{

        if( x->l->size==pos )
			x->val=val;
        else if( x->l->size >= pos + 1 )
            replace( x->l, pos , val);
        else
			replace( x->r, pos - x->l->size - 1 , val);
        x->update();
    }

    node query( int lo, int hi, int a, int b, node *x )
	{
        if( a > hi || b < lo || x == dummy ) return *dummy;
        if( a >= lo && b <= hi ) return *x;

		node l = query( lo, hi, a, a + x->l->size - 1, x->l ) ;
		node r = query( lo, hi, a + x->l->size + 1, b, x->r ) ;

		int id  = a + x->l->size ;
		int on = ( id >= lo && id<=hi) ;
		int val  = on ? x->val : -inf;
		int val2 = on ? x->val : 0;
		LL best=-inf,pref,suf,sum;;


		sum  = l.sum + val2+ r.sum;

		best= MAX(best,val+MAX3(l.suf,r.pref,l.suf+r.pref));
		best= MAX(best,MAX3(val,l.best,r.best));

		pref= MAX3(l.pref , l.sum + val, l.sum + val2 + r.pref);
		suf = MAX3(r.suf  , r.sum + val, r.sum + val2 + l.suf );

		node ret;
		ret.sum=sum;ret.pref=pref;ret.suf=suf;ret.best=best;
        return ret;
    }

	void insert(int pos, int val ) { root = insert( root, pos, val); }
	void erase(int pos) { root = erase( root, pos); }
	void replace( int pos, int val ) { replace( root, pos, val); }
    LL query( int lo, int hi ) { return (query( lo, hi, 0, root->size - 1, root )).best; }
} T;


int n,arr[100005],best[100005];


int bf(char ch,int x,int y)
{
	int i,j,ret=-inf;

	if(ch=='R') arr[x]=y;
	if(ch=='D')
	{
		for(i=x;i<n-1;i++) arr[i]=arr[i+1];--n;
	}
	if(ch=='I')
	{
		for(i=n-1;i>=x;i--) arr[i+1]=arr[i];
		arr[x]=y;++n;
	}
	if(ch=='Q')
	{
		best[x]=0;
		for(i=x;i<=y;i++)
		{
			best[i+1]=MAX(arr[i],best[i]+arr[i]);
			ret=MAX(ret,best[i+1]);
		}
	}

	//for(i=0;i<n;i++) printf("%d ",arr[i]);puts("");
	return ret;
}

int main()
{
    int i,j,m,sign[2];
	sign[0]=+1,sign[1]=-1;

	scanf( "%d", &n );

	for(i=0;i<n;i++)
	{
		//int co=sign[rand()%2];int v=rand()%10001;arr[i]=co*v;printf("%d ",arr[i]);
		scanf("%d",&arr[i]);
		T.insert(i,arr[i]);
	}


	scanf("%d",&m);

	for(i=1;i<=m;i++)
	{
		char type[5];
		int x,y,xx;


		/*char str[6]="IDRQ";
		type[0]=str[rand()%4];x=rand()%n+1;xx= x!=n ? x : x-1;
		y= type[0]!='Q' ? rand()%10001 : x+rand()%(n-xx);
		if(x==n) y=x;
		printf("%c %d %d\n",type[0],x,y);*/

		scanf("%s%d",type,&x);if(type[0]!='D') scanf("%d",&y);

		//int ans= type[0]!='Q' ? bf(type[0],x-1,y) : bf(type[0],x-1,y-1);

		if(type[0]=='I')
			T.insert(x-1,y);
		if(type[0]=='R')
			T.replace(x-1,y);
		if(type[0]=='D')
			T.erase(x-1);
		if(type[0]=='Q')
			printf("%d\n",T.query(x-1,y-1));
	}


    return 0;
}
