#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 103
int MIN(int a, int b)
{
    if (a<b) return a;
    else return b;
}
char input[1000];
int dfsnum[MAX],dfslevel[MAX],low[MAX],children[MAX],matrix[MAX][MAX],articulation[MAX],ARTIC,dfscounter,N,E;
void APDFS(int node)
{
    int i;
    dfsnum[node] = dfscounter++;
    low[node] = dfsnum[node];
    /*printf("\t%d %d",node,low[node]);*/
    for (i=1; i<=N; i++)
    {
        if (matrix[node][i])
        {
            if (dfsnum[i]==-1)
            {
                dfslevel[i] = dfslevel[node] + 1;
                children[node]++;
                children[i]++;
                APDFS(i);
                low[node] = MIN(low[node],low[i]);
                if (dfsnum[node]==1)
                {
                    if (children[node]>=2 && articulation[node]==0)
                    {
                        articulation[node] = 1;
                        /*printf("articulation : %d\n",node);*/
                        ARTIC++;
                    }
                }
            }
            else
            {
                if (low[i]>=dfsnum[node] && articulation[node]==0)
                {
                    articulation[node] = 1;
                    /*printf("articulation : %d\n",node);*/
                    ARTIC++;
                }
            }
        }
        else
        {
            if (dfslevel[i]<dfslevel[node]-1)
            {
                dfsnum[i] = dfscounter;
                low[node] = MIN(low[node],dfsnum[i]);
            }
        }
    }
    /*printf("\t%d %d\n",node,low[node]);*/
}
int main()
{
    int i,j,x,cost;
    char *ch;
    while(scanf("%d",&N) && N)
    {
        ARTIC = dfscounter = 0;
        for (i=1; i<=N; i++)
        {
            low[i] = 30609;
            dfsnum[i] = -1;
            children[i] = 0;
            articulation[i] = 0;
            for (j=1; j<=N; j++) matrix[i][j] = 0;
        }
        /*scanf("%d",&E);
        for (x=1; x<=E; x++)
        {
            scanf("%d%d",&i,&j);
            matrix[i][j] = matrix[j][i] = 1;
        }*/
        getchar();
        while(gets(input) && strcmp(input,"0"))
        {
            ch = strtok(input," ");
            x = atoi(ch);
            while((ch = strtok(NULL," "))!=NULL)
            {
                matrix[x][atoi(ch)] = matrix[atoi(ch)][x] = 1;
            }
        }
        for (i=1; i<=N; i++)
        {
            for (j=1; j<=N; j++)
            {
                low[j] = 30609;
                dfsnum[j] = -1;
                children[j] = 0;
            }
            dfslevel[i] = dfscounter = 0;
            APDFS(i);
        }
        printf("\t%d\n",ARTIC);
        /*for (i=1; i<=N; i++) printf("%d :: dfsnum : %d\tdfslevel : %d\tlow : %d\n",i,dfsnum[i],dfslevel[i],low[i]);*/
    }
    return 0;
}
/* 8
10
1 2
1 3
2 3
3 4
3 5
3 7
4 5
5 6
6 7
6 8

17
21
1 14
1 11
6 7
10 15
8 10
8 15
14 11
14 1
9 7
9 12
3 1
7 12
4 8
13 17
13 7
17 6
5 11
11 8
2 5
16 9
15 17*/
