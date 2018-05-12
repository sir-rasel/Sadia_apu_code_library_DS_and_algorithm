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
long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a%b);
}
#define MAXN 106
long long array[MAXN], soln[MAXN];
void run(int N, long long M, long long r)
{
    int i;
    tripple t;
    long long g,C;
    for (; N>=1; --N)
    {
        t = ext_euclid(soln[N],M);
        g = t.d, t.b *= -1;
        if (N == 1)
        {
            soln[N] = (t.a % M) * ((r/g) % M);
            soln[N] = (soln[N] % M + M) % M;
            return;
        }
        C = (t.a % M) * (r/g);
        t = ext_euclid(soln[N-1],array[N]);
        soln[N] = (t.b % M) * (C % M);
        soln[N] = (soln[N] % M + M) % M;
        r = ((r-array[N]*soln[N])%M + M)%M;
    }
}
int main()
{
    //freopen("data.txt", "r", stdin);
    long long r,M,g;
    int T,N,i;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (i=1; i<=N; ++i) scanf("%lld", &array[i]);
        scanf("%lld %lld", &r, &M);
        r %= M;
        for (i=1; i<=N; ++i)
        {
            array[i] %= M;
            soln[i] = gcd(soln[i-1],array[i]);
        }
        g = gcd(soln[N],M);
        if (r%g)
        {
            puts("NO");
            continue;
        }
        run(N,M,r%M);
        printf("%lld", soln[1]);
        for (i=2; i<=N; ++i) printf(" %lld", soln[i]);
        puts("");
    }
    return 0;
}
