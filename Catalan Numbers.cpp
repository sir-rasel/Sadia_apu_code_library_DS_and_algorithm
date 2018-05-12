#include<stdio.h>
int main()
{
    long long milo[101][101]={0};
    long long i,j,res;

    for ( j=1; j<=100; j++) milo[j][1]=j;

    for ( i=2; i<=100; i++)
    {
        for ( j=2; j<=i; j++)
        {
            milo[i][j]=milo[i-1][j]+milo[i-1][j-1];
        }
    }
    long long n;
    while(scanf("%lld",&n)!=EOF)
    {
        long long ans = milo[2*n][n];
        ans /= (n+1);
        printf("%lld\n",ans);
    }

    return 0;
}


