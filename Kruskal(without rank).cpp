#include<stdio.h>
#include<algorithm>
using namespace std;
#define MAXEDGE 103
#define MAXN 20
int n_node,E,parent[MAXN];
struct edges
{
    int start,end,cost;
} edge[MAXEDGE];
bool cmp(edges a, edges b)
{
    return b.cost>a.cost;
}
void initialise_all()
{
    for (int i=0; i<MAXN; i++)
    {
        parent[i]=i;
    }
}
int search_parent(int node)
{
    if (parent[node]==node) return node;
    else return search_parent(parent[node]);
}
int main()
{
    int i,total_cost,parent_start,parent_end;
    while(scanf("%d",&n_node)!=EOF)
    {
        scanf("%d",&E);
        for (i=0; i<E; i++) scanf("%d%d%d",&edge[i].start,&edge[i].end,&edge[i].cost);
        sort (edge, edge+E, cmp);
        initialise_all();
        total_cost = 0;
        puts("");
        for (i=0; i<E; i++)
        {
            parent_start = search_parent(parent[edge[i].start]);
            parent_end = search_parent(parent[edge[i].end]);
            if (parent_start == parent_end) continue;
            if (parent_start == edge[i].start && parent_end == edge[i].end)
            {
                parent[edge[i].end]=parent[edge[i].start];
            }
            else if (parent_start == edge[i].start)
            {
                parent[edge[i].start] = parent_end;
            }
            else if (parent_end == edge[i].end)
            {
                parent[edge[i].end] = parent_start;
            }
            else
            {
                parent[parent_end] = parent_start;
            }
            printf("%d %d %d\n",edge[i].start,edge[i].end,edge[i].cost);
            total_cost += edge[i].cost;
        }
        printf("total cost : %d\n",total_cost);
    }
    return 0;
}
