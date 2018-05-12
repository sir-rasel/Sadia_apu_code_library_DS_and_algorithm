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
#include<assert.h>
#include<iostream>
using namespace std;
#define MAXN 100006
struct vv
{
    int sum;
    vv *l,*r;
    vv () {sum = 0, l = r = NULL;}
    vv (int val) {sum = val;}
    vv (vv *_l, vv *_r)
    {
        l = _l, r = _r, sum = 0;
        if (l != NULL) sum += l->sum;
        if (r != NULL) sum += r->sum;
    }
};
int arr[MAXN];
vector < vv * > V;
vv *build(int left, int right)
{
    if (left == right) return new vv(arr[left]);
    int mid = (left + right) / 2;
    vv *l = build(left, mid), *r = build(mid+1,right);
    return new vv (l,r);
}
vv *update(vv *tree, int left, int right, int idx, int val)
{
    if (left == right) return new vv(val);
    int mid = (left + right) / 2;
    vv *l, *r;
    if (idx <= mid)
    {
        l = update(tree->l, left, mid, idx, val);
        r = tree->r;
    }
    else
    {
        l = tree->l;
        r = update(tree->r, mid+1, right, idx, val);
    }
    return new vv (l,r);
}
int query(vv *tree, int left, int right, int start, int end)
{
    if (end < left || right < start) return 0;
    if (start <= left && right <= end) return tree->sum;
    int mid = (left + right) / 2;
    return query(tree->l, left, mid, start, end) + query(tree->r, mid+1, right, start, end);
}
int main()
{
    int N,i,idx,val,x,y;
    while (scanf("%d", &N) != EOF)
    {
        V.clear();
        for (i=1; i<=N; ++i) scanf("%d", &arr[i]);
        V.push_back(build(1,N));
        printf("initial sum = %d\n", V[0]->sum);
        /*while (scanf("%d %d", &idx, &val) != EOF)
        {
            V.push_back(update(V.back(), 1,N, idx,val));
            printf("sum = %d\n", V.back()->sum);
        }*/
        while (scanf("%d %d", &x, &y) != EOF) printf("%d %d : %d\n", x,y, query(V.back(), 1,N, x,y));
    }
    return 0;
}
