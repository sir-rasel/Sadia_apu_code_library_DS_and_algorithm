#include<stdio.h>
#define MAX 100
long long quo[MAX],rem[MAX],X[MAX],Y[MAX],d,i;
long long GCD(long long a,long long b)
{
    if (!a && b) return b;
    else if (a && !b) return a;
    if (b==0) return a;
    else return GCD(b,a%b);
}
void e_euclid(long long a, long long b)
{
    if (b==1)
    {
        printf("%lld %lld %lld\n",X[i-1],Y[i-1],d);
        return;
    }
    rem[i]=a%b;
    quo[i]=a/b;
    X[i]=X[i-2]-X[i-1]*quo[i];
    Y[i]=Y[i-2]-Y[i-1]*quo[i];
    e_euclid(b,rem[i++]);
}
int main()
{
    long long a,b;

    while(scanf("%lld%lld",&a,&b)!=EOF)
    {
        d = GCD(a,b);
        if (a==0)
        {
            printf("0 1 %lld\n",b);
            continue;
        }
        else if (b==0)
        {
            printf("1 0 %lld\n",a);
            continue;
        }
        else if (a==b)
        {
            printf("0 1 %lld\n",a);
            continue;
        }
        else if (a==1)
        {
            printf("1 0 1\n");
            continue;
        }
        else if (b==1)
        {
            printf("0 1 1\n");
            continue;
        }
        a/=d;
        b/=d;
        if (a==1)
        {
            printf("1 0 %lld\n",d);
            continue;
        }
        else if (b==1)
        {
            printf("0 1 %lld\n",d);
            continue;
        }
        rem[1]=a%b;
        quo[1]=a/b;
        X[1]=1;
        Y[1]=(-1)*quo[1];
        a=b;
        b=rem[1];
        if (b==1)
        {
            printf("%lld %lld %lld\n",X[1],Y[1],d);
            continue;
        }
        rem[2]=a%b;
        quo[2]=a/b;
        X[2]=(-1)*quo[2];
        Y[2]=1-Y[1]*quo[2];
        a=b;
        b=rem[2];
        if (b==1)
        {
            printf("%lld %lld %lld\n",X[2],Y[2],d);
            continue;
        }
        i=3;
        e_euclid(a,b);
    }
    return 0;
}
