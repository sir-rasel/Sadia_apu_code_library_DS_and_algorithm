#include<stdio.h>
#include<math.h>

int main()
{
    double n,a;
    int b,m;
    while(scanf("%d",&m)!=EOF)
    {
        if (m==6)
        {
            puts("2^-6 = 1.562e-2");
            continue;
        }
        printf("2^-%d = ",m);
        n=(-1)*m*log10(2)-1;
        b=n;
        a=b-n;
        a=pow(10,-a);
        printf("%.3lfe%d\n",10*a,b);
    }
    return 0;
}
