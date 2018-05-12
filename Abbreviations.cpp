headers
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<iostream>
#include<assert.h>
using namespace std;
int main()
{

    return 0;
}

abso
#define ABSO(x) ((x)>0?(x):(-(x)))

bigmod2
int bigmod(int a, int k, int MOD)
{
    if (k==0) return 1;
    if (k%2) return (int) (((long long) a*bigmod(a,k-1,MOD))%MOD);
    long long ret = bigmod(a, k/2, MOD);
    return (int) ((ret*ret) % MOD);
}

bigmodint
int bigmod(int a, __int64 k)
{
    if (k==0) return 1;
    if (k%2) return ((__int64) a*bigmod(a,k-1))%MOD;
    __int64 ret = bigmod(a, k/2);
    return (int) ((ret*ret) % MOD);
}

BST
struct node
{
    int val, subsize;
    node *left, *right;
    node(int v) {val = v, subsize = 1, left = right = NULL;}
};
class BST
{
    node *head;
    void insert(int val, node *now)
    {
        ++now->subsize;
        if (val < now->val)
        {
            if (now->left == NULL)
            {
                now->left = new node(val);
                return;
            }
            else insert(val, now->left);
        }
        else
        {
            if (now->right == NULL)
            {
                now->right = new node(val);
                return;
            }
            else insert(val, now->right);
        }
    }
    long long calc(node *now)
    {
        if (now == NULL) return 1;
        long long left, right, ret;
        left = calc(now->left);
        right = calc(now->right);
        ret = (left * right) % MOD;
        if (now->left != NULL && now->right != NULL) ret = ret * rec(now->left->subsize, now->right->subsize);
        if (now->left != NULL) delete now->left;
        if (now->right != NULL) delete now->right;
        return ret % MOD;
    }
public:
    BST(int n) { head = new node(n); }
    void insert(int n) { insert(n,head); }
    long long calc() { return calc(head); }
};

divisor
#define RANGE 100006
bool sieve[RANGE];
int fprime[RANGE];
vector < pair < int , int > > ppf;
vector < int > divset;
void primeTable()
{
    int i,j;
    int lim = sqrt((double) RANGE)+6;
    memset(fprime, -1, sizeof(fprime));
    fprime[2] = 2;
    for (i=4; i<RANGE; i+=2) sieve[i] = true, fprime[i] = 2;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            fprime[i] = i;
            for (j=i*i; j<RANGE; j += (i<<1))
            {
                sieve[j] = true;
                if (fprime[j] == -1) fprime[j] = i;
            }
        }
    }
    for (; i<RANGE; i+=2)
    {
        if (!sieve[i]) fprime[i] = i;
    }
}
void factor(int N)
{
    ppf.clear();
    int p = fprime[N], f=0;
    while(N != 1)
    {
        p = fprime[N], f=0;
        while(fprime[N]==p)
        {
            ++f;
            N /= p;
        }
        ppf.push_back(make_pair(p,f));
    }
}
void divisor(int N)
{
    factor(N);
    divset.clear();
    divset.push_back(1);
    int i,j,f,p,m,exs;
    for (i=0; i<ppf.size(); ++i)
    {
        p = ppf[i].first, f = ppf[i].second;
        m = 1, exs = divset.size();
        while(f--)
        {
            m *= p;
            for (j=0; j<exs; ++j) divset.push_back(divset[j]*m);
        }
    }
    sort(divset.begin(), divset.end());
    //for (i=0; i<divset.size(); ++i) printf("%d ", divset[i]); puts("");
}

divisor2
#define RANGE 1000001
vector <int> Primes;
vector < pair <long long, int> > ppf;
vector < long long > divset;
bool sieve[RANGE+6];
void primeTable()
{
    int i,j;
    Primes.clear();
    Primes.push_back(2);
    int lim = sqrt((double) RANGE)+2;
    for (i=4; i<RANGE; i+=2) sieve[i] = true;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            Primes.push_back(i);
            for (j=i*i; j<=RANGE; j += (i<<1)) sieve[j] = true;
        }
    }
    for (; i<RANGE; i+=2)
    {
        if (!sieve[i]) Primes.push_back(i);
    }
}
void factor(long long N)
{
    ppf.clear();
    long long n = N,p;
    int freq,i;
    for (i = 0; n != 1 && i < Primes.size(); ++i)
    {
        p = Primes[i];
        if (Primes[i] > sqrt((double) n)+1) break;
        if (n % p == 0)
        {
            freq = 0;
            while(n % p == 0)
            {
                n /= p;
                ++freq;
            }
            ppf.push_back(make_pair(p, freq));
        }
    }
    if (n>1) ppf.push_back(make_pair(n, 1));
    //for (i=0; i<ppf.size(); ++i) printf("%lld %d", ppf[i].first, ppf[i].second);
}
void divisor(long long N)
{
    factor(N);
    divset.clear();
    divset.push_back(1);
    long long p,m;
    int i,j,f,exs;
    for (i=0; i<ppf.size(); ++i)
    {
        p = ppf[i].first, f = ppf[i].second;
        m = 1, exs = divset.size();
        while(f--)
        {
            m *= p;
            for (j=0; j<exs; ++j) divset.push_back(divset[j]*m);
        }
    }
    sort(divset.begin(), divset.end());
    //for (i=0; i<divset.size(); ++i) printf("%d ", divset[i]); puts("");
}

floyd_warshall
#define MAXN 106
int fw[MAXN][MAXN];
void initialize(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) fw[i][j] = INF;
        fw[i][i] = 0;
    }
}
void floyd_warshall(int N)
{
    int i,j,k,temp;
    for (k=0; k<N; ++k)
    {
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j)
            {
                temp = fw[i][k] + fw[k][j];
                if (temp < fw[i][j]) fw[i][j] = temp;
            }
        }
    }
}

matrix
#define SIZE 4
class Matrix
{
public:
    int N;
    int matrix[SIZE][SIZE];
    Matrix(int n) {N = n;}
    int getDim() {return N;}
    void setZer() {memset(matrix, 0, sizeof(matrix));}
    void setOne()
    {
        int i;
        setZer();
        for (i=0; i<N; ++i) matrix[i][i] = 1;
    }
    void setVal(int array[][SIZE])
    {
        int i,j;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) matrix[i][j] = array[i][j];
        }
    }
    Matrix operator+ (Matrix &A)
    {
        Matrix ret(N);
        int i,j;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) ret.matrix[i][j] = (matrix[i][j] + A.matrix[i][j]) % MOD;
        }
        return ret;
    }
    Matrix operator* (Matrix &A)
    {
        Matrix ret(N);
        int i,j,k;
        long long temp;
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j)
            {
                ret.matrix[i][j] = 0;
                for (k=0; k<N; ++k)
                {
                    temp = (long long) matrix[i][k] * A.matrix[k][j];
                    ret.matrix[i][j] = (ret.matrix[i][j] + temp)%MOD;
                }
            }
        }
        return ret;
    }
    void printMatrix()
    {
        int i,j;
        puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        for (i=0; i<N; ++i)
        {
            for (j=0; j<N; ++j) printf("%3d ", matrix[i][j]);
            puts("");
        }
        puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    }
} base(SIZE), ret(SIZE);
Matrix bigmod(Matrix A, int K)
{
    if (K==1) return base;
    if (K&1)
    {
        ret = bigmod(A, K-1);
        ret = ret * base;
        return ret;
    }
    ret = bigmod(A, K>>1);
    ret = ret*ret;
    return ret;
}
Matrix bigmodmat2(Matrix base, int K)
{
    ret = base;
    Matrix ans(base.N);
    ans.setOne();
    while (K)
    {
        if (K % 2) ans = ans * ret;
        K /= 2;
        ret = ret * ret;
    }
    return ans;
}

maxmin
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))

nCr
int nCr[MAXN][MAXN];
void gen_nCr()
{
    int i,j;
    nCr[0][0] = 1;
    for (i=1; i<MAXN; ++i) nCr[i][1] = i, nCr[i][0] = nCr[i][i] = 1;
    for (i=2; i<MAXN; ++i)
    {
        for (j=2; j<i; ++j) nCr[i][j] = (nCr[i-1][j] + nCr[i-1][j-1])%MOD;
    }
}

phi
char sieve[RANGE];
int phi[RANGE];
void primeTable()
{
    long i,j;
    for (i=2; i<RANGE; ++i)
    {
        if (!sieve[i])
        {
            phi[i]= i-1;
            for (j=i+i; j<RANGE; j+=i) sieve[j]=1;
        }
        else
        {
            for (j=2; j<i; ++j)
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
}

sieve
#define RANGE 1000001
bool sieve[RANGE];
void primeTable()
{
    int i,j;
    int lim = sqrt((double) RANGE)+2;
    for (i=4; i<RANGE; i+=2) sieve[i] = true;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            for (j=i*i; j<=RANGE; j += (i<<1)) sieve[j] = true;
        }
    }
}

sieveprime
#define RANGE 10000001
bool sieve[RANGE];
vector < int > Primes;
void primeTable()
{
    int i,j;
    int lim = sqrt((double) RANGE)+2;
    Primes.push_back(2);
    for (i=4; i<RANGE; i+=2) sieve[i] = true;
    for (i=3; i<lim; i+=2)
    {
        if (!sieve[i])
        {
            Primes.push_back(i);
            for (j=i*i; j<=RANGE; j += (i<<1)) sieve[j] = true;
        }
    }
    for (; i<RANGE; i+=2)
    {
        if (!sieve[i]) Primes.push_back(i);
    }
}

nCr2
void pre()
{
    int i;
    fact[0] = 1;
    for (i=1; i<MAXL; ++i) fact[i] = ((long long) fact[i-1] * i) % MOD;
}
int bigmod(int a, int k)
{
    if (k==0) return 1;
    if (k%2) return ((long long) a*bigmod(a,k-1))%MOD;
    long long ret = bigmod(a, k/2);
    return (int) ((ret*ret) % MOD);
}
