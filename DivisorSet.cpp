#include<stdio.h>
#include<math.h>
#include<set>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
#define RANGE 1000001
set <int> S, Primes;
set <int> :: iterator is;
vector < pair <int, int> > V;
queue <int> Q;
bool sieve[RANGE+3];
void primeTable()
{
    int i,j;
    Primes.clear();
    Primes.insert(2);
    int lim = sqrt((double) RANGE)+2;
    for (i=2; i<RANGE; i+=2) sieve[i] = true;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            Primes.insert(i);
            for (j=i*i; j<=RANGE; j += (i<<1)) sieve[j] = true;
        }
    }
    for (; i<RANGE; i+=2)
    {
        if (!sieve[i]) Primes.insert(i);
    }
}
void PPF(int N)
{
    V.clear();
    int n = N, freq;
    for (is = Primes.begin(); n != 1 && is != Primes.end(); ++is)
    {
        if (n % *is == 0)
        {
            freq = 0;
            while(n % *is == 0)
            {
                n /= *is;
                ++freq;
            }
            V.push_back(make_pair(*is, freq));
        }
    }
    if (n>1) V.push_back(make_pair(n, 1));
    puts("prime frequency:");
    for (int i=0; i<V.size(); ++i) printf("%d %d\n", V[i].first, V[i].second);
    puts("--");
}
void factor(int N)
{
    PPF(N);
    while(!Q.empty()) Q.pop();
    S.clear();
    Q.push(1);
    int i,x,y;
    long long temp;
    while(!Q.empty())
    {
        x = Q.front();
        Q.pop();
        for (i=0; i<V.size(); ++i)
        {
            temp = (long long) x * (long long) V[i].first;
            if (temp>N) break;
            y = x * V[i].first;
            if (N%y == 0 && S.find(y) == S.end() && y<N)
            {
                S.insert(y);
                Q.push(y);
            }
        }
    }
    printf("%d divisors:\n", S.size());
    for (is = S.begin(); is != S.end(); ++is) printf("%d\n", *is);
}
int main()
{
    primeTable();
    int i,c;
    factor(1053*1053); // S has the set ;)
    /*for (i=2,c=0; i<=500; ++i)
    {
        if (!sieve[i]) printf("%d : %d\n", ++c, i);
    }*/
    return 0;
}
