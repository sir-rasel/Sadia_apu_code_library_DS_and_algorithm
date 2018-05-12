// Perimeter Union
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXSIZE 30000
int full[MAXSIZE*12], nonzero[MAXSIZE*12];
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
void update(int node, int left, int right, int start, int end, int val)
{
    if (start <= left && right <= end)
    {
        full[node] += val;
        if (full[node]==0) nonzero[node] = nonzero[2*node] + nonzero[2*node+1];
        else nonzero[node] = (right-left+1);
        return;
    }
    if (right<start || end<left || left==right) return;
    int mid = (left+right)/2;
    update(2*node, left, mid, start, end, val);
    update(2*node+1, mid+1, right, start, end, val);
    if (full[node]==0) nonzero[node] = nonzero[2*node] + nonzero[2*node+1];
    else nonzero[node] = (right-left+1);
}
long long findPerimeter(int RANGE)
{
    sort(array.begin(), array.end(), cmp);
    memset(full, 0, sizeof(full));
    memset(nonzero, 0, sizeof(nonzero));
    int i,lastx = array[0].x;
    long long ret = 0;
    for (i=0; i<array.size(); ++i)
    {
        ret += nonzero[1];
        update(1, 1, RANGE, array[i].ly, array[i].uy, array[i].t?1:-1);
        lastx = array[i].x;
    }
    return ret;
}
struct rectangle
{
    int lx,ly,ux,uy;
    rectangle(int lxx, lyy, uxx, uyy) {lx=lxx, ly=lyy, ux=uxx, uy=uyy;}
};
vector < rectangle > R;
int proc()
{
    int i,N=rectangle.size(),Y=-1;
    array.clear();
    for (i=0; i<R.size(); ++i)
    {
        array.push_back(edge(R.lx, R.ly+10002, R.uy+10001, 1));
        array.push_back(edge(R.ux, R.ly+10002, R.uy+10001, 0));
        if (R.uy+10001>Y) Y = R.uy+10001;
    }
    return Y;
}
void swap(int &x, int &y)
{
    int z = x;
    x = y;
    y = z;
}
void rev()
{
    int i;
    for (i=0; i<R.size(); ++i)
    {
        swap(R.lx, R.ly);
        swap(R.ux, R.uy);
    }
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int N,i;
    int lx,ly,ux,uy,Y;
    long long ans;
    while(scanf("%d", &N) != EOF)
    {
        array.clear(); R.clear();
        Y = -1;
        for (i=1; i<=N; ++i)
        {
            scanf("%d %d %d %d", &lx, &ly, &ux, &uy);
            R.push_back(rectangle(lx,ly,ux,uy));
        }
        ans = findPerimeter(proc());
        rev();
        ans += findPerimeter(proc());
        printf("%lld\n", ans);
    }
    return 0;
}
