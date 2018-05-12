// Segmented Sieve
#include<stdio.h>
#define RANGE 46343
long long primes[48000],P=0;
char sieve[RANGE];
bool array[1000003];
void prime_table()
{
    long long i,j;
    for (i=4; i<RANGE; i+=2) sieve[i] = 1;
    primes[P++] = 2;
    for (i=3; i<RANGE; i+=2)
    {
        if (!sieve[i])
        {
            primes[P++] = i;
            for (j=i+i; j<RANGE; j+=i) sieve[j] = 1;
        }
    }
}
int main()
{
    long long i,j;
    long long L,U,d,D;
    long long difference;
    long long count;
    prime_table();
    int t,T;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%lld %lld",&L,&U);
        D = U - L;
        difference = L;
        for (i=0; i<=D; ++i) array[i] = 0;
        if (L==1) array[0] = 1;
        for (j=0; j<P; ++j)
        {
            if (primes[j]>U) break;
            d = L/primes[j];
            if (primes[j]*d<L) d++;
            if (d==1) ++d;
            for (i=d; ;++i)
            {
                if(primes[j]*i>U) break;
                if (primes[j]*i>=L) array[primes[j]*i-difference] = 1;
            }
        }
        /*for (i=0; i<=D; ++i) printf("%d : %d\n",i+L,array[i]);*/
        count = 0;
        for (i=0; i<=D; ++i)
        {
            if (array[i]==0) ++count;
        }
        printf("Case %d: %lld\n", t, count);
    }
    return 0;
}
