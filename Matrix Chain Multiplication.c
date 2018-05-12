#include<stdio.h>
#define MAXSIZE 103
#define INF 30000000
long M[MAXSIZE][MAXSIZE],S[MAXSIZE][MAXSIZE];
long P[MAXSIZE+1];
void MCM(long n)
{
    long i,j,k,x,l;
    for (i=1; i<=n; i++) M[i][i] = 0;
    for (l=2; l<=n; l++)
    {
        for (i=1; i<= n-l+1; i++)
        {
            j = i+l-1;
            M[i][j] = INF;
            for (k=i; k<j; k++)
            {
                x = M[i][k] + M[k+1][j] + P[i-1]*P[k]*P[j];
                if (x<M[i][j])
                {
                    M[i][j] = x;
                    S[i][j] = k;
                }
            }
        }
    }
}
void print_path(long i, long j)
{
    if (i==j) printf("A%ld",i);
    else
    {
        printf("(");
        print_path(i,S[i][j]);
        printf("*");
        print_path(S[i][j]+1,j);
        printf(")");
    }
}
int main()
{
    long n,a,b,p;
    while(scanf("%ld",&n) && n)
    {
        scanf("%ld%ld",&a,&b);
        P[0] = a;
        P[1] = b;
        p = 2;
        while(p<=n)
        {
            scanf("%ld%ld",&a,&b);
            P[p++] = b;
        }
        MCM(n);
        printf("%ld\n",M[1][n]);
        print_path(1,n);
        puts("");
    }
    return 0;
}
