#include<stdio.h>
#define MAX 2000001
long phi[MAX];
char sieve[MAX];
int main()
{
    long i,j,t;
    for (i=1;i<MAX;i++) phi[i]=i;
    for (i=2; i<MAX; i++)
    {
        if(!sieve[i])
        {
            phi[i]=i-1;
            for(j=2*i;j<MAX;j+=i)
            {
                phi[j]/=i;
                phi[j]*=i-1;
                sieve[j]=1;
            }
        }
    }
    scanf("%ld",&t);
    while(t--)
    {
        scanf("%ld",&i);
        printf("%ld\n",phi[i]);
    }
    return 0;
}
