#include<stdio.h>
#include<math.h>
long long m;
long long divide_conquer_fibo(long long n)
{
    long long i,j,k,h,t;
    i = h = 1;
    j = k = 0;
    while(n)
    {
        if (n%2)
        {
            t = (j*h)%m;
            j = (i*h + j*k + t)%m;
            i = (i*k + t)%m;
        }
        t = (h*h)%m;
        h = (2*k*h + t)%m;
        k = (k*k + t)%m;
        n /=2;
    }
    return j%m;
}
int main()
{
    long long n;
    m=100000000;
    while(scanf("%lld%lld",&n,&m)!=EOF)
    {
        m = pow(2,m);
        printf("%lld\n",divide_conquer_fibo(n));
    }
    return 0;
}
