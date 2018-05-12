#include<stdio.h>
#include<iostream>
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
using namespace std;
#define EPS 0.00000000000001
struct line
{
    double m,c;
};
struct point
{
    double x,y;
};
stack < line > S;
vector < line > array;
bool cmpl(line a, line b)
{
    if (fabs(a.m-b.m) < EPS) return a.c < b.c;
    return a.m > b.m;
}
point intersection(line a, line b)
{
    point ret;
    ret.x = ((b.c-a.c)/(a.m-b.m));
    ret.y = ((a.c*b.m-b.c*a.m)/(b.m-a.m));
    return ret;
}
void takeIn(int N)
{
    double m,c;
    int i;
    for (i=0; i<N; ++i)
    {
        scanf("%lf %lf", &m, &c);
        l.m = m, l.c = c;
        array.push_back(l);
    }
}
void prepStack()
{
    while(!S.empty()) S.pop();
    int i;
    line l;
    point last,temp;
    for (i=0; i<array.size(); ++i)
    {
        l = array[i];
        if (S.empty())
        {
            S.push(l);
            continue;
        }
        while(!S.empty())
        {
            temp = intersection(S.top(),l);
            if (temp.x <= last.x) S.pop();
            if (!S.empty()) last =
        }
    }
}
int main()
{
    int N,i;
    double m,c;
    line l;
    while(scanf("%d", &N) != EOF)
    {
        array.clear();
        takeIn(N);
        sort(array.begin(), array.end(), cmpl);
        prepStack();
    }
    return 0;
}
/*
test
line a,b;
    a.m = 1, b.m = -1;
    a.c = 0, b.c = 2;
    point s = intersection(a,b);
    printf("%lf %lf\n", s.x, s.y);accumulate
    */
