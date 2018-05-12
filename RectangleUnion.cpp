// Rectangle Union
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
#define MAXSIZE 30000
int full[MAXSIZE*18], nonzero[MAXSIZE*18]; //#times full node taken, #of nonzero cells
struct edge
{
    int x, ly, uy;
    bool t;
    edge(int xx, int lyy, int uyy, bool tt) {x=xx, ly=lyy, uy=uyy, t=tt;}
};
bool cmp(edge a, edge b)
{
    return a.x < b.x;
}
vector < edge > array;
set < int > S;
map < int , int > M;
int rm[MAXSIZE*4+6];
void proc()
{
    int i;
    set < int > :: iterator is;
    for (is = S.begin(), i = 1; is != S.end(); ++is, ++i)
    {
        M[*is] = i;
        rm[i] = *is;
    }
}
void update(int node, int left, int right, int start, int end, int val)
{
    if (start <= left && right <= end)
    {
        full[node] += val;
        if (full[node]==0) nonzero[node] = nonzero[2*node] + nonzero[2*node+1];
        else nonzero[node] = (rm[right]-rm[left-1]);
        return;
    }
    if (right<start || end<left || left==right) return;
    int mid = (left+right)/2;
    update(2*node, left, mid, start, end, val);
    update(2*node+1, mid+1, right, start, end, val);
    if (full[node]==0) nonzero[node] = nonzero[2*node] + nonzero[2*node+1];
    else nonzero[node] = (rm[right]-rm[left-1]);
}
long long findArea()
{
    int RANGE = S.size();
    sort(array.begin(), array.end(), cmp);
    memset(full, 0, sizeof(full));
    memset(nonzero, 0, sizeof(nonzero));
    int i,lastx = array[0].x;
    long long ret = 0;
    for (i=0; i<array.size(); ++i)
    {
        ret += nonzero[1] * (long long) (array[i].x-lastx);
        update(1, 1, RANGE, M[array[i].ly], M[array[i].uy], array[i].t?1:-1);
        lastx = array[i].x;
    }
    return ret;
}
int main()
{
    int N,i;
    int t,T;
    int lx,ly,ux,uy;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        array.clear(); S.clear(); M.clear();
        for (i=1; i<=N; ++i)
        {
            scanf("%d %d %d %d", &lx, &ly, &ux, &uy);
            if (lx==ux || ly==uy) continue;
            ly+=3, uy+=2;
            array.push_back(edge(lx, ly, uy, 1));
            array.push_back(edge(ux, ly, uy, 0));
            S.insert(ly); S.insert(uy);
            S.insert(ly-1); S.insert(uy-1);
        }
        proc();
        printf("Case %d: %lld\n", t, findArea());
    }
    return 0;
}
