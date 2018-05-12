#include<stdio.h>
#include<math.h>
#define EPS 1e-6
#define SIZE 50
double matrix[SIZE+3][SIZE+3];
void swap(int N, int r1, int r2)
{
    if (r1==r2) return;
    double temp;
    int j;
    for (j=1; j<=N; ++j)
    {
        temp = matrix[r1][j];
        matrix[r1][j] = matrix[r2][j];
        matrix[r2][j] = temp;
    }
}
int findRow(int N, int r)
{
    int j = r;
    while(j<=N)
    {
        if (!(fabs(matrix[j][r])<EPS)) return j;
        ++j;
    }
    return -1;
}
void printMatrix(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        for (j=1; j<=N; ++j) printf("%.3lf ", matrix[i][j]);
        puts("");
    }
    puts("");
}
double DeterminantByGaussianElimination(int N)
{
    int i,j,k;
    double f = 1.0;
    for (i=1; i<=N; ++i)
    {
        j = findRow(N,i);
        if (j==-1) return 0.0;
        swap(N,i,j);
        if (i != j) f = -f;
        for (j=i+1; j<=N; ++j)
        {
            for (k=N; k>=i; --k) matrix[j][k] -= matrix[j][i] * matrix[i][k] / matrix[i][i];
        }
    }
    for (i=1; i<=N; ++i) f *= matrix[i][i];
    return f;
}
int main()
{
    //freopen("data.txt", "r", stdin);
    int N, i, j;
    while(scanf("%d", &N) != EOF)
    {
        for (i=1; i<=N; ++i)
        {
            for (j=N+1; j<=N; ++j) matrix[i][j] = 0;
            matrix[i][N+i] = 1;
            for (j=1; j<=N; ++j) scanf("%lf", &matrix[i][j]);
        }
        printf("%.3lf\n", DeterminantByGaussianElimination(N));
    }
    return 0;
}
