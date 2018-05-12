#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MAX 10000
#define INF 100000001
struct point
{
    double x,y;
} points[MAX+3], backup[MAX+3];
double dist(point a, point b)
{
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
bool cmpx(point a, point b)
{
    return a.x < b.x;
}
bool cmpy(point a, point b)
{
    return a.y < b.y;
}
double rec(int start, int end)
{
    if (start>=end) return INF;
    if (start+1 == end) return(dist(points[start], points[end]));
    int mid = (start+end)>>1;
    double left, right, mini, d;
    left = rec(start, mid);
    right = rec(mid+1, end);
    mini = MINI(left, right);
    int b = 0, i,j;
    i = mid;
    while(i>=start && (points[mid].x-points[i].x)*(points[mid].x-points[i].x)<mini) backup[b++] = points[i--];
    i = mid+1;
    while(i<=end && (points[i].x-points[mid].x<mini)*(points[i].x-points[mid].x<mini)) backup[b++] = points[i++];
    sort (backup, backup+b, cmpy);
    for (i=0; i<b; ++i)
    {
        for (j=1; j<=6 && i+j<b; ++j)
        {
            if ((backup[i+j].y-backup[i].y)*(backup[i+j].y-backup[i].y) >= mini) break;
            d = dist(backup[i], backup[i+j]);
            mini = MINI(mini, d);
        }
    }
    return mini;
}
int main()
{
    int N, i, j;
    double ans;
    while(scanf("%d",&N)!=EOF && N)
    {
        for (i=0; i<N; ++i) scanf("%lf %lf",&points[i].x, &points[i].y);
        sort (points, points+N, cmpx);
        if (N<2)
        {
            puts("INFINITY");
            continue;
        }
        ans = rec(0, N-1);
        if (ans>=0 && ans<100000000) printf("%.4lf\n",sqrt(ans));
        else puts("INFINITY");
    }
    return 0;
}
