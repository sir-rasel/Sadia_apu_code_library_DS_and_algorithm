#include<stdio.h>
#include<string.h>
#define MAX 1003
int c[MAX][MAX];
int b[MAX][MAX];
char X[MAX], Y[MAX];
int LCS (int m, int n)
{
    int i,j;
    for (i=0; i<m; i++)
    {
        for (j=0; j<n; j++) b[i][j]= c[i][j] = 0;
    }
    for (i=1; i<=m; i++)
    {
        for (j=1; j<=n; j++)
        {
            if (X[i-1] == Y[j-1])
            {
                b[i][j] = 1;
                c[i][j] = 1 + c[i-1][j-1];
            }
            else if (c[i][j-1]>= c[i-1][j])
            {
                b[i][j] = 2;
                c[i][j] = c[i][j-1];
            }
            else
            {
                b[i][j] = 3;
                c[i][j] = c[i-1][j];
            }
        }
    }
    return c[m][n];
}
void print_LCS(int m, int n)
{
    if (m==-1 || n==-1) return;
    if (b[m][n]==1)
    {
        print_LCS(m-1,n-1);
        printf("%c",X[m-1]);
    }
    else if (b[m][n]==2) print_LCS(m,n-1);
    else print_LCS(m-1,n);
}
int main()
{
    int m,n;
    while(scanf("%s%s",X,Y)!=EOF)
    {
        m = strlen(X);
        n = strlen(Y);
        printf("%d   ",LCS(m,n));
        print_LCS(m,n);
        puts("");
    }
    return 0;
}
