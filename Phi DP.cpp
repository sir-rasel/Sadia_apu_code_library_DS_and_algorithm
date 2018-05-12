#include<stdio.h>
#define MAX 2000001
long phi[MAX];
char sieve[MAX];
int main()
{
    long i,j,t;
    phi[1]=0;
    for (i=2; i<MAX; i++)
    {
        if (!sieve[i])
        {
            for (j=i+i; j<MAX; j+=i) sieve[j]=1;
            phi[i]= i-1;
        }
        else
        {
            for (j=2; j<i; j++)
            {
                if (i%j==0)
                {
                    if (i%(j*j)==0) phi[i]= j*phi[i/j];
                    else phi[i]= (j-1)*phi[i/j];
                    break;
                }
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
