#include<stdio.h>
long long ans ( long long b, long long p, long long m)
{
    if (p==0) return 1;
    if (p%2)
    {
        return ((b%m)*ans(b,p-1,m))%m;
    }
    else
    {
        long long backup = ans(b,p/2,m)%m;
        return (backup*backup)%m;
    }
}
int main()
{
    long long b,p,m;
    while(scanf("%lld%lld%lld",&b,&p,&m)!=EOF) printf("%lld\n",ans(b,p,m));
    return 0;
}
