#include<stdio.h>
#define MAX 100
int capacity[MAX+3][MAX+3];
int flow [MAX+3][MAX+3];
bool visited [MAX+3];
struct
{
    int node, parent, cap;
} queue[MAX];
void initialise(int N)
{
    int i,j;
    for (i=0; i<N; ++i)
    {
        for (j=0; j<N; ++j) capacity[i][j] = flow[i][j] = 0;
    }
}
int MINI(int a, int b)
{
    if (a<b) return a;
    return b;
}
int bfs(int N, int source, int dest, int &cap)
{
    int i, start, end, now;
    for (i=0; i<N; ++i) visited[i] = false;
    start = end = 0;
    queue[end].node = source;
    queue[end].parent = -1;
    queue[end++].cap = 100;
    visited[source] = true;
    while(start<end)
    {
        now = queue[start].node;
        if (now == dest)
        {
            cap = queue[start].cap;
            return start;
        }
        for (i=0; i<N; ++i)
        {
            if (capacity[now][i]>0 && !visited[i])
            {
                visited[i] = true;
                queue[end].node = i;
                queue[end].cap = MINI(queue[start].cap, capacity[now][i]);
                queue[end++].parent = start;
            }
        }
        ++start;
    }
    return -1;
}
void get_flow(int pos, int cap)
{
    if (pos == -1) return;
    int parent = queue[queue[pos].parent].node;
    int child = queue[pos].node;
    capacity[parent][child] -= cap;
    capacity[child][parent] += cap;
    flow[parent][child] += cap;
    flow[child][parent] -= cap;
    get_flow(queue[pos].parent,cap);
}
int main()
{
    int i,N,E,end,source,dest,x,y,c,maxflow;
    while(scanf("%d%d",&N,&E)!=EOF)
    {
        scanf("%d%d",&source,&dest);
        initialise(N);
        while(E--)
        {
            scanf("%d%d%d",&x,&y,&c);
            capacity[x][y] += c;
        }
        end = bfs(N,source,dest,c);
        while(end>-1)
        {
            get_flow(end,c);
            end = bfs(N,source,dest,c);
        }
        maxflow = 0;
        for (i=0; i<N; ++i) maxflow += flow[i][dest];
        printf("%d\n",maxflow);
    }
    return 0;
}
/*
7 8
0 6
0 1 3
1 3 3
0 2 1
2 3 5
3 6 2
2 4 4
4 5 2
5 6 3
*/
