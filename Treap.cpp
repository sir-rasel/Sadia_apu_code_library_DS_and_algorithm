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
#include<time.h>
using namespace std;
struct node
{
    int val, prior, sz;
    node *l, *r;
    int lval,rval,ans;
    node() {}
    node(int _val, int _prior) {val = _val, prior = _prior, l=r=NULL, sz=1, lval=rval=val, ans=0;}
    void updatesz()
    {
        int lsz, rsz;
        lsz = rsz = 0;
        if (l != NULL) lsz = l->sz;
        if (r != NULL) rsz = r->sz;
        sz = lsz + 1 + rsz;
    }
    void updateans()
    {
        ans = 0;
        lval = rval = val;
        if (l != NULL) lval = l->lval, ans += l->ans + (l->rval == val);
        if (r != NULL) rval = r->rval, ans += r->ans + (r->lval == val);
    }
    void updaten() {updatesz(); updateans();}
};
void print(node *now)
{
    if (now == NULL) return;
    print(now->l);
    printf("(%d %d %d %d [%d %d]) ", now->val, now->prior, now->sz, now->ans, now->lval, now->rval);
    //printf("%d ", now->val);
    print(now->r);
}
int findsz(node *n)
{
    if (n == NULL) return 0;
    return n->sz;
}
void split(node* T, node* &L, node* &R, int key)
{
    if (T == NULL)
    {
        L = R = NULL;
        return;
    }
    int cur = findsz(T->l);
    if (key <= cur)
    {
        split(T->l, L, T->l, key);
        R = T;
    }
    else
    {
        split(T->r, T->r, R, key-(cur+1));
        L = T;
    }
    T->updaten();
}
void merge(node* &T, node* L, node* R)
{
    if (L == NULL) T = R;
    else if (R == NULL) T = L;
    else if (L->prior >= R->prior)
    {
        merge(L->r, L->r, R);
        T = L;
    }
    else
    {
        merge(R->l, L, R->l);
        T = R;
    }
    if (T != NULL) T->updaten();
}
void insert(node* &tree, int x)
{
    node *temp = new node(x,rand());
    merge(tree, tree, temp);
}
node *insert(node* tree, int p, int x)
{
    node *temp = new node(x,rand());
    node *L,*R;
    split(tree, L,R, p);
    merge(L, L, temp);
    merge(tree, L, R);
    return tree;
}
node *del(node *tree, int p)
{
    if (tree == NULL || p == 0 || tree->sz < p) return tree;
    node *L,*R;
    split(tree, L,R, p);
    split(L, tree,L, p-1);
    if (L != NULL) delete L;
    merge(tree, tree,R);
    return tree;
}
void clr(node *tree)
{
    if (tree == NULL) return;
    if (tree->l) clr(tree->l);
    if (tree->r) clr(tree->r);
    delete tree;
}
node *update(node *tree, int left, int right)
{
    if (left == 1) return tree;
    node *L,*R,*M;
    split(tree, L,R, right);
    split(L, L,M, left-1);
    merge(tree, M,L);
    merge(tree, tree,R);
    return tree;
}
int gans;
node *findans(node *tree, int left, int right)
{
    node *L,*R,*M;
    split(tree, L,R, right);
    split(L, L,M, left-1);
    gans = M->ans;
    merge(tree, L,M);
    merge(tree, tree,R);
    return tree;
}
int main()
{
    srand(time(NULL));
    node *tree = NULL;
    int op,x,p;
    int Q = rand()%100+1;
    char ch = '0';
    while (Q--)
    {
        if (ch == 'q') op = 1;
        else op = rand()%2;
        if (tree == NULL || op == 0)
        {
            p = rand()%(findsz(tree)+1);
            x = rand()%36+1;
            printf("insert p=%d x=%d\n", p,x);
            tree = insert(tree, p, x);
        }
        else
        {
            p = rand()%(findsz(tree)) + 1;
            printf("delete %d\n", p);
            tree = del(tree, p);
        }
        print(tree); puts("");
        ch = getch();
    }
    printf("final : "); print(tree); puts("");
    return 0;
}
