#include<stdio.h>
#include<conio.h>
#define SIEVEMAX 10000001
bool sieve[SIEVEMAX]= {false};
void advanced_sieve(void)
{
    long long i,j;
    for (i=4; i<SIEVEMAX; i+=2) sieve[i]=true;
    for (i=3; i<SIEVEMAX; i+=2)
    {
        if (sieve[i]==false)
        {
            for (j=i*i; ; j+=2*i)
            {
                if (j>=SIEVEMAX) break;
                sieve[j]=true;
            }
        }
    }
    return;
}
int main()
{

    return 0;
}
