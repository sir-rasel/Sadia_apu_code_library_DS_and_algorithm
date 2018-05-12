#pragma comment(linker, "/STACK:67108864")
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200006
struct Node;
Node * nil, * root;
struct Node
{
    Node * child[2], * parent;
    int key, value, size;
    int sum,lazy;
    Node( int key, int value = 0 )
    {
        child[0] = child[1] = parent = nil;
        this->key = key;
        this->value = value;
        size = 1;
        sum = value;
        lazy = 0;
   }
};
void initTree( void )
{
    nil = new Node( 0 );
    nil->child[0] = nil->child[1] = nil->parent = nil;
    nil->value = nil->size = nil->sum = 0;
    root = nil;
}
void pushDown( Node * x )
{
    if( x == nil ) return;
    if( x->lazy ){
        x->value += x->lazy;
        x->child[0]->lazy += x->lazy;
        x->child[1]->lazy += x->lazy;
        x->lazy = 0;
    }
}

int getSum( Node *x )
{
    if( x == nil ) return 0;
    return x->sum + x->lazy*x->size;
}
void update( Node * x )
{
    if( x == nil ) return;
    pushDown( x );
    x->size = x->child[0]->size + x->child[1]->size + 1;//printf("here size %d %d\n",x->key,x->size );
    x->sum = getSum( x->child[0] ) + getSum( x->child[1] ) + x->value;
}
void setLink( Node * x, Node * y, int d )
{
    x->child[d] = y;
    y->parent = x;
}
int getDir( Node * x, Node * y )
{
    return x->child[0] == y ? 0 : 1;
}
void rotate( Node * x, int d )
{
    Node * y = x->child[d], * z = x->parent;
    pushDown( z ); pushDown( x ); pushDown( y );
    setLink( x, y->child[d ^ 1], d );
    setLink( y, x, d ^ 1 );
    setLink( z, y, getDir( z, x ) );
    update( x ); update( y ); update( z );
}
void splay( Node * x )
{
    while( x->parent != nil )
    {
        Node * y = x->parent, * z = y->parent;
        int dy = getDir( y, x ), dz = getDir( z, y );
        if( z == nil ) rotate( y, dy );
        else if( dy == dz ) rotate( z, dz ), rotate( y, dy );
        else rotate( y, dy ), rotate( z, dz );
    }
    root = x;
}
Node * nodeAt( Node * x, int pos )
{
    while( pushDown( x ), x->child[0]->size+1 != pos )
    {
        if( pos <= x->child[0]->size ) x = x->child[0];
        else pos -= x->child[0]->size + 1, x = x->child[1];
    }
    return splay( x ), x;
}
int search( Node * x, int pos )
{
    while( pushDown( x ), !(x->value == 1 && x->child[0]->sum+1 == pos) )
    {
        if( pos <= x->child[0]->sum ) x = x->child[0];
        else pos -= x->child[0]->sum + x->value, x = x->child[1];
    }
    return splay( x ), x->key;
}
void splitRight( Node * mid, Node * &t1, Node * &t2 )
{
    splay( mid );
    t1 = mid;
    t2 = t1->child[1];
    t1->child[1] = t2->parent = nil;
    update( t1 );
    update( t2 );
}
void splitLeft( Node * mid, Node * &t1, Node * &t2 )
{
    splay( mid );
    t2 = mid;
    t1 = t2->child[0];
    t2->child[0] = t1->parent = nil;
    update( t1 );
    update( t2 );
}
Node * join( Node * x, Node * y )
{
    while( x==nil and y==nil );
    if( x == nil ) return y;
    if( y == nil ) return x;
    splay( x );
    splay( y );
    x = nodeAt( x, x->size );
    setLink( x, y, 1 );
    update( x );
    update( y );
    return x;
}
void print(Node *root)
{
    if (root == nil) return;
    printf("%3d : %3d %3d : %3d %3d : %3d\n", root->key, root->value, root->sum, root->child[0]->key, root->child[1]->key, root->size);
    print(root->child[0]);
    print(root->child[1]);
}

int N;
vector<int> ed[MAXN];
Node * stPtr[MAXN];
Node * edPtr[MAXN];
bool vis[MAXN];
void bfs( void )
{
    memset(vis, false, sizeof(vis));
    queue<int> q;
    int i;
    stPtr[0] = new Node( 1, 1 );
    edPtr[0] = new Node( -1, 0 );
    setLink( stPtr[0], edPtr[0], 1 );
    update( stPtr[0] );
    root = stPtr[0];
    vis[0] = true;
    q.push( 0 );
    while( !q.empty() )
    {
        int u = q.front();
        q.pop();
        for( i=0;i<ed[u].size();i++ )
        {
            int v = ed[u][i];
            if (vis[v]) continue;
            stPtr[v] = new Node( v+1, 1 );
            edPtr[v] = new Node( -(v+1), 0 );
            setLink( stPtr[v], edPtr[v], 1 );
            update( stPtr[v] );
            Node * t1, *t2;
            splitLeft(  edPtr[u], t1, t2 );
            root = join( t1,stPtr[v] );
            root = join( root,t2 ); ///splay//cout<<root->size<<" "<<root->sum<<endl;
            vis[v] = true;
            q.push( v );
        }
    }
}
void update(int u, int v)
{
    Node *t1, *t2, *t3, *t4;
    splitLeft(stPtr[u], t1, t2);
    splitRight(edPtr[u], t3, t4);
    root = join(t1,t4);
    Node *t5, *t6;
    splitLeft(edPtr[v], t5, t6);
    root = join(t5,t3);
    root = join(root,t6);
}
int main( void )
{
    //freopen("data.txt","r",stdin );
    int T,Q,i,u,v,k = 0,op;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d",&N );
        for( i=0;i<N;i++ ) ed[i].clear();
        for( i=1;i<N;i++ )
        {
            scanf("%d%d",&u,&v); --u,--v;
            ed[u].push_back(v);
            ed[v].push_back(u);
        }
        initTree();
        bfs();///splay( root = stPtr[0] );cout<<root->size<<" "<<root->sum<<endl;
        scanf("%d", &Q);
        while (Q--)
        {
            scanf("%d", &op);
            if (op == 1)
            {
                scanf("%d %d", &u, &v); --u,--v;
                update(u,v);
            }
            else
            {
                scanf("%d", &k);
                printf("%d\n", search(root, k));
            }
            //print(root);
        }
    }
    return 0;
}
