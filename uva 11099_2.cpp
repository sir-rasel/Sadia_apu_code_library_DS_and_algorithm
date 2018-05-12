#include<stdio.h>
#define SIEVE 1000001
#define TEST 2000001
#define MAX 1000001
#define INF 1000000000
long long primes[78500],uprimes[15];
char sieve[SIEVE];
long long res[TEST/2];
long long primecheck( long long n)
{
    if( n==1) return 0;
    long long a,b=5;
    for ( a=2; a*a<=n; a+=2)
    {
        if ( n%a == 0)
        {
            b=0;
            return 0;
            break;
        }
        if (a==2) a-=1;
    }
    if (b) return n;
}

int isprime( long long n)
{
    if (n<SIEVE)
    {
        if (sieve[n]) return 0;
        else return 1;
    }
    else 
    {
        if (primecheck(n)) return 1;
        else return 0;
    }
}
int main()
{
    long long i,j,np=1,k,temp;
    for (i=2; i<SIEVE; i++)
    {
        if (!sieve[i])
        {
            primes[np++]=i;
            for (j=i*2; j<SIEVE; j+=i) sieve[j]=1;
        }
    }
    long long n,m,p,gcd,u,x,start=1, end=1,ans=1;
    while(scanf("%lld",&n)!=EOF)
    {
/*        printf("\t");*/
        if (n<2)
        {
            printf("Not Exist!\n");
            continue;
        }
        ans= INF;
        u=1;
        gcd=1;
        m=n;
        for (j=1; m!=1 ; j++)
        {
            if (m%primes[j]==0)
            {
                x= primes[j];
                uprimes[u++]=x;
                gcd*=x;
                while(m%x==0) m/=x;
                if (m==1) break;
                if (isprime(m))
                {
                    gcd*=m;
                    uprimes[u++]=m;
                    break;
                }
            }
        }
/*        for (i=1; i<u; i++) printf("%lld ",uprimes[i]); 
        printf("\n%lld ",gcd); 
*/        if (u==2)
        {
            ans= n*gcd;
        }
        else
        {
            res[end++]=gcd;
            while(start<end)
            {
                for (i=1; i<u; i++)
                {
                    temp= res[start]*uprimes[i];
                    if (temp<ans)
                    {
                        res[end++]=temp;
                        if (temp<=n) continue;
                        ans = temp;
                    }
                    else break;
                }
                start++;
            }
        }
        if (ans<TEST) printf("%lld\n",ans);
        else printf("Not Exist!\n"); 
    }
    return 0;
}
    
    
