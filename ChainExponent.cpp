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
#define MAXN 16
#define MAXM 10006
int phi[MAXM];
bool sieve[MAXM];
int array[MAXN];
#define RANGE 10006
int fprime[RANGE];
void primeTable()
{
    int i,j,t;
    int lim = sqrt((double) RANGE)+6;
    memset(fprime, -1, sizeof(fprime));
    fprime[2] = 2;
    for (i=4; i<RANGE; i+=2) sieve[i] = true, fprime[i] = 2;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            fprime[i] = i;
            for (j=i*i; j<RANGE; j += (i<<1))
            {
                sieve[j] = true;
                if (fprime[j] == -1) fprime[j] = i;
            }
        }
    }
    for (; i<RANGE; i+=2)
    {
        if (!sieve[i]) fprime[i] = i;
    }
    for (i=1;i<MAXM;i++) phi[i]=i;
    for (i=2; i<MAXM; i++)
    {
        if(!sieve[i])
        {
            phi[i]=i-1;
            for(j=2*i;j<MAXM;j+=i)
            {
                phi[j]/=i;
                phi[j]*=i-1;
            }
        }
    }
}
void factor(int N, vector < pair < int , int > > &ppf)
{
    ppf.clear();
    int p = fprime[N], f=0;
    while(N != 1)
    {
        p = fprime[N], f=0;
        while(fprime[N]==p)
        {
            ++f;
            N /= p;
        }
        ppf.push_back(make_pair(p,f));
    }
}
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
int bigmod(int a, int k, int MOD)
{
    if (k==0) return 1;
    if (k%2) return (int) (((long long) a*bigmod(a,k-1,MOD))%MOD);
    long long ret = bigmod(a, k/2, MOD);
    return (int) ((ret*ret) % MOD);
}
pair < int , double > calc(int x, int y)
{
    if (x == y) return make_pair(0,(double) array[x]);
    pair < int , double > ret = calc(x+1,y);
    return make_pair(1+ret.first, ret.second*log10((double) array[x]));
}
int check(int x, int y, int thr)
{
    if (x == y) return array[x] <= thr ? array[x] : -1;
    int p = 1, i;
    for (i=y; i>=x; --i)
    {
        if (p > 13) return -1;
        if (p * log10((double) array[i]) > log10(thr)) return -1;
        p = bigmod(array[i],p,thr+1);
    }
    return p;
}
int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a%b);
}
int calcfreq(int n, int p)
{
    int ret = 0;
    while (n%p == 0)
    {
        ++ret;
        n /= p;
    }
    return ret;
}
int rec(int N, int n, int M)
{
    if (N == 1) return array[1]%M;
    if (M == 1) return 0;
    if (n+1 == N) return bigmod(array[n],array[N],M);
    if (gcd(array[n],M) == 1) return bigmod(array[n],rec(N,n+1,phi[M]),M);
    vector < pair < int , int > > ppf;
    factor(M,ppf);
    int i,p,f,b,pw;
    vector < pair < int , int > > V;
    for (i=0; i<ppf.size(); ++i)
    {
        p = ppf[i].first, f = ppf[i].second, b = bigmod(p,f,M+1);;
        if (array[n]%p)
        {
            f = bigmod(array[n],rec(N,n+1,phi[b]),b);
            V.push_back(make_pair(b,f));
            continue;
        }
        pw = check(n+1,N,f);
        if (pw != -1) pw *= calcfreq(array[n],p);
        if (pw == -1 || pw >= f) V.push_back(make_pair(b,0));
        else V.push_back(make_pair(b,bigmod(array[n],pw,b)));
    }
    b = CRT(V);
    return (int) b;
}
int main()
{
    //freopen("data.txt", "r", stdin);
    primeTable();
    int T=0,N,M,i;
    char str[10];
    while (scanf("%s", str) && str[0] != '#')
    {
        sscanf(str, "%d", &M);
        scanf("%d", &N);
        for (i=1; i<=N; ++i) scanf("%d", &array[i]);
        for (i=1; i<=N && array[i] != 1; ++i);
        if (i<=N) N = i-1;
        if (N < 1)
        {
            printf("Case #%d: %d\n", ++T,1%M);
            continue;
        }
        printf("Case #%d: %d\n", ++T,rec(N,1,M));
    }
    return 0;
}
/*
if(a,c) coprime
(a^b)%c = ( a^(b%phi(c)) ) %c
else if(b>=phi(c))
(a^b)%c = ( a^(b%phi(c) + phi(c)) ) %c
else (a^b)%c = (a^b)%c
*/
