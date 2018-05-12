#include<stdio.h>
#include<string.h>
using namespace std;
#define SIZE 50
#define INF 100
int matrix[SIZE+3][SIZE+3], original[SIZE+3][SIZE+3];
void minRowDel(int N)
{
    int i,j,mini;
    for (i=0; i<N; ++i)
    {
        mini = INF;
        for (j=0; j<N; ++j)
        {
            if (matrix[i][j]<mini) mini = matrix[i][j];
        }
        for (j=0; j<N; ++j) matrix[i][j] -= mini;
    }
}
void minColDel(int N)
{
    int i,j,mini;
    for (j=0; j<N; ++j)
    {
        mini = INF;
        for (i=0; i<N; ++i)
        {
            if (matrix[i][j]<mini) mini = matrix[i][j];
        }
        for (i=0; i<N; ++i) matrix[i][j] -= mini;
    }
}
bool RowMark[SIZE+3], ColMark[SIZE+3];
int RowLeft[SIZE+3];
void initRows(int N)
{
    int i,j;
    memset(RowLeft, false, sizeof(RowLeft));
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            if (!matrix[i][j]) ++RowLeft[i];
        }
    }
}
int findMinRow(int N)
{
    int i,j,mini=INF,indx=-1;
    bool f;
    for (i=0; i<N; ++i)
    {
        if (!RowMark[i] && RowLeft[i] && RowLeft[i]<mini)
        {
            mini = RowLeft[i];
            indx = i;
        }
    }
    return indx;
}
int matchRow[SIZE+3];
void markAll(int N)
{
    int i,j,mini=INF,indx;
    memset(RowMark, false, sizeof(RowMark));
    memset(ColMark, false, sizeof(ColMark));
    initRows(N);
    indx = findMinRow(N);
    while(indx != -1)
    {
        for (j=0; j<N; ++j)
        {
            if (!ColMark[j] && !matrix[indx][j])
            {
                ColMark[j] = true;
                RowMark[indx] = true;
                matchRow[indx] = j;
                for (i=0; i<N; ++i)
                {
                    if (!RowMark[i] && !matrix[i][j]) --RowLeft[i];
                }
                break;
            }
        }
        indx = findMinRow(N);
    }
}
bool tickedRow[SIZE+3], tickedCol[SIZE+3];
void nowCol(int, int);
void nowRow(int N, int r)
{
    if (tickedRow[r]) return;
    tickedRow[r] = true;
    int j;
    for (j=0; j<N; ++j)
    {
        if (matrix[r][j]==0) nowCol(N,j);
    }
}
void nowCol(int N, int c)
{
    if (tickedCol[c]) return;
    tickedCol[c] = true;
    int i;
    for (i=0; i<N; ++i)
    {
        if (matchRow[i] == c)
        {
            nowRow(N,i);
            break;
        }
    }
}
void findTicks(int N)
{
    int i,j;
    memset(tickedRow, false, sizeof(tickedRow));
    memset(tickedCol, false, sizeof(tickedCol));
    for (i=0; i<N; ++i)
    {
        if (!RowMark[i]) nowRow(N,i);
    }
}
int findTheta(int N)
{
    int i,j,mini = INF;
    for (i=0; i<N; ++i)
    {
        if (!tickedRow[i]) continue;
        for (j=0; j<N; ++j)
        {
            if (tickedCol[j]) continue;
            if (matrix[i][j])
            {
                if (matrix[i][j] && matrix[i][j]<mini) mini = matrix[i][j];
            }
        }
    }
    return mini;
}
void adjTheta(int N, int theta)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            if (!tickedRow[i] && tickedCol[j]) matrix[i][j] += theta;
            else if (!tickedRow[i] || tickedCol[j]) continue;
            else matrix[i][j] -= theta;
        }
    }
}
int countLines(int N)
{
    int ret = 0, i;
    for(i=0; i<N; ++i)
    {
        if (!tickedRow[i]) ++ret;
        if (tickedCol[i]) ++ret;
    }
    return ret;
}
int match(int N)
{
    minRowDel(N);
    minColDel(N);
    markAll(N);
    findTicks(N);
    int i,j,ret=0,theta;
    while(countLines(N) != N)
    {
        theta = findTheta(N);
        adjTheta(N, theta);
        markAll(N);
        findTicks(N);
    }
    for (i=0; i<N; ++i)
    {
        /*printf("%d %d\n", i, matchRow[i]);*/
        ret += original[i][matchRow[i]];
    }
    return ret;
}
void takeInput(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j)
        {
            scanf("%d", &original[i][j]);
            matrix[i][j] = original[i][j];
        }
    }
}
int main()
{
    int N;
    while(scanf("%d", &N)!=EOF && N>0)
    {
        takeInput(N);
        printf("Minimum Weight : %d\n", match(N));
    }
    return 0;
}
/*printf("theta = %d\n",theta);
        printf("ticked rows : ");
        for (i=0; i<N; ++i)
        {
            if (tickedRow[i]) printf("%d ", i);
        }
        puts("");
        printf("ticked cols : ");
        for (i=0; i<N; ++i)
        {
            if (tickedCol[i]) printf("%d ", i);
        }
        puts("");*/
