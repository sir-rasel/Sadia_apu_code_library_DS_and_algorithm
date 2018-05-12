// Finding Polynomial Series Coefficients
#include<stdio.h>
#include<math.h>
#define EPS 1e-6
#define SIZE 53
double matrix[SIZE][SIZE];
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
void swap(int N, int r1, int r2)
{
    if (r1==r2) return;
    double temp;
    int j;
    for (j=1; j<=N+1; ++j)
    {
        temp = matrix[r1][j];
        matrix[r1][j] = matrix[r2][j];
        matrix[r2][j] = temp;
    }
}
void printMatrix(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        for (j=1; j<=2*N; ++j) printf("%.3lf ", matrix[i][j]);
        puts("");
    }
    puts("");
}
bool GaussianElimination(int N)
{
    int i,j,k;
    for (i=1; i<=N; ++i)
    {
        j = findRow(N,i);
        if (j==-1) return false;
        swap(N,i,j);
        for (j=N+1; j>=i; --j) matrix[i][j] /= matrix[i][i];
        for (j=i+1; j<=N; ++j)
        {
            for (k=N+1; k>=i; --k) matrix[j][k] -= matrix[j][i] * matrix[i][k];
        }
    }
    for (i=N; i>=1; --i)
    {
        for (j=i-1; j>=1; --j)
        {
            for (k=N+1; k>=i; --k) matrix[j][k] -= matrix[j][i] * matrix[i][k];
        }
    }
    return true;
}
void printSolution(int N)
{
    int i;
    for (i=1; i<=N; ++i) printf("coeff of n^%d : %.9lf\n", N-i, matrix[i][N+1]);
}
long long sols[SIZE] = {1, 12, 57, 176, 425, 876, 1617, 2752};
int sls;
int findOrder()
{
    long long backup[SIZE];
    int i,j,n;
    for (i=0; i<sls; ++i) backup[i] = sols[i];
    for (n=0,j=sls-1; n<sls; ++n,--j)
    {
        if (j < 2) return -1;
        if (backup[1] == backup[2]) break;
        for (i=0; i<j; ++i) backup[i] = backup[i+1] - backup[i];
    }
    if (n < sls) return n;
    return -1;
}
int main()
{
    int N, i, j, k;
    //sls = 8;
    while(scanf("%d", &sls) != EOF)
    {
        for (i=0; i<sls; ++i) scanf("%lld", &sols[i]);
        N = findOrder();
        if (N == -1)
        {
            puts("no valid polynomial series");
            continue;
        }
        ++N;
        for (i=1; i<=N; ++i)
        {
            k = 1;
            for (j=1; j<=N; ++j)
            {
                matrix[i][N-j+1] = k;
                k *= i;
            }
            matrix[i][N+1] = sols[i-1];
        }
        //printMatrix(N);
        if (GaussianElimination(N)) printSolution(N);
        else puts("Infinite No. of Solutions");
    }
    return 0;
}
