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
using namespace std;
#define ABSO(x) ((x)>0?(x):(-(x)))
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
struct tripple
{
    long long d,a,b;
    tripple() {}
    tripple(long long _d, long long _a, long long _b) {a=_a, b=_b, d=_d;}
};
tripple ext_euclid(long long a, long long b) // solves ax + by = gcd(a,b) :: returns(x,y)
{
    if (b == 0) return tripple(a,1,0);
    tripple t = ext_euclid(b,a%b);
    return tripple(t.d, t.b, t.a-(a/b)*t.b);
}
pair < long long , long long > numsol(long long z, long long e, long long z1, long long z2)
{
    if (z1 > z2) swap(z1,z2);
    z1 -= z, z2 -= z;
    if (e < 0)
    {
        swap (z1, z2);
        z1 *= -1, z2 *= -1, e *= -1;
    }
    if (z1 % e == 0) z1 /= e;
    else
    {
        if (z1 >= 0) z1 = z1/e + 1;
        else z1 = z1/e;
    }
    if (z2 % e == 0) z2 /= e;
    else
    {
        if (z2 >= 0) z2 = z2 / e;
        else z2 = z2 / e - 1;
    }
    return make_pair(z1,z2);
}
long long numofsol(long long a, long long b, long long c, long long x1, long long x2, long long y1, long long y2) ///ax + by = c
{
    if (a == 0 && b == 0)
    {
        if (c) return 0;
        return (x2-x1+1) * (y2-y1+1);
    }
    bool fa = a<0, fb = b<0;
    tripple t = ext_euclid(ABSO(a),ABSO(b));
    //printf("\t\t%lld %lld\n", t.a, t.b);
    long long g = t.d;
    if (c%g) return 0;
    if (a == 0)
    {
        long long y = c / b;
        if (y1 <= y && y <= y2) return x2-x1+1;
        return 0;
    }
    if (b == 0)
    {
        long long x = c / a;
        if (x1 <= x && x <= x2) return y2-y1+1;
        return 0;
    }
    if (fa) t.a *= -1;
    if (fb) t.b *= -1;
    t.a *= (c/g);
    t.b *= (c/g);
    pair < long long , long long > in1, in2, p;
    in1 = numsol(t.a,b/g,x1,x2);
    in2 = numsol(t.b,-a/g,y1,y2);
    p = make_pair(MAXI(in1.first,in2.first), MINI(in1.second,in2.second));
    if (p.first > p.second) return 0;
    return p.second - p.first + 1;
}
long long CRT(vector < pair < int , int > > V)
{
    long long prod = 1, ans = 0, a;
    int i,p,r;
    tripple t;
    for (i=0; i<V.size(); ++i) prod *= V[i].first;
    for (i=0; i<V.size(); ++i)
    {
        p = V[i].first, r = V[i].second;
        a = prod / p;
        t = ext_euclid(a,p);
        ans += a * t.a * r;
        ans %= prod;
    }
    if (ans < 0) ans += prod;
    return ans;
}
int main()
{
    long long a,b,c,x1,x2,y1,y2;
    /*while (scanf("%lld %lld %lld %lld %lld %lld %lld", &a, &b, &c, &x1, &x2, &y1, &y2) != EOF) /// ax+by=c
    {
        printf("%lld\n", numofsol(a,b,c,x1,x2,y1,y2));
    }*/
    vector < pair < int , int > > V;
    V.push_back(make_pair(2,0));
    V.push_back(make_pair(5,2));
    printf("%d\n", CRT(V));
    return 0;
}
