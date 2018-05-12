// Number of MSTs in a Graph
#include<stdio.h>
#include<iostream>
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
using namespace std;
#define EPS 1e-6
#define SIZE 56
long double matrix[SIZE][SIZE], backup[SIZE][SIZE];
int deg[SIZE];
set < pair < int , int > > S;
void swap(int N, int r1, int r2)
{
    if (r1==r2) return;
    long double temp;
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
        for (j=1; j<=N; ++j) printf("%.3Lf ", matrix[i][j]);
        puts("");
    }
    puts("");
}
long double DeterminantByGaussianElimination(int N)
{
    int i,j,k;
    long double f = 1.0;
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
long double abs(long double x)
{
    if (x < 0.0) return -x;
    return x;
}
int main()
{
    int N, M, i, j, k, l, root, x, y;
    long double ans;
    while(scanf("%d %d %d", &N, &M, &root) != EOF)
    {
        for (i=1; i<=N; ++i)
        {
            deg[i] = N-1;
            for (j=1; j<=N; ++j) matrix[i][j] = (long double) 1.0;
            matrix[i][i] = (long double) 0.0;
        }
        S.clear();
        while(M--)
        {
            scanf("%d %d", &x, &y);
            if (x > y) swap(x,y);
            if (S.find(make_pair(x,y)) == S.end()) S.insert(make_pair(x,y));
            else continue;
            matrix[x][y] = matrix[y][x] = (long double) 0.0;
            --deg[x], --deg[y];
        }
        for (i=1; i<=N; ++i)
        {
            for (j=1; j<=N; ++j)
            {
                if (i == j) matrix[i][j] = (long double) deg[i];
                else matrix[i][j] = -matrix[i][j];
            }
        }
        for (i=1; i<=N; ++i)
        {
            for (j=1; j<=N; ++j) backup[i][j] = matrix[i][j];
        }
        ans = abs(DeterminantByGaussianElimination(N-1));
        cout.precision(0);
        cout << fixed << ans << endl;
    }
    return 0;
}
