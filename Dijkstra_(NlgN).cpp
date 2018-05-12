#include<stdio.h>
#include<algorithm>
#define MAXINT 32762
#define RANGE 100
using namespace std;
void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}
int MINI(int a, int b)
{
    if (a<b) return a;
    return b;
}
struct node
{
    int node, cost;
} ad_list[RANGE][RANGE];
bool cmp (node a, node b)
{
    return a.cost<b.cost;
}
int V_cost[RANGE], nl[RANGE];
void sort_list(int N)
{
    int i,j;
    for (i=1; i<=N; ++i)
    {
        sort(ad_list[i]+1,ad_list[i]+nl[i], cmp);
    }
}
class PQ
{
    public:
    int AA[RANGE],MAX,indx;
    PQ() {indx = 1;}
    int front() {return AA[1];}
    void push(int val);
    void pop();
    void print() {for (int i=1; i<indx; ++i) printf("%d ",AA[i]); puts("");};
};
void PQ :: push(int val)
{
    int parent, now = indx++;
    AA[now] = val;
    parent = now>>1;
    while(parent)
    {
        if (V_cost[AA[parent]]>V_cost[AA[now]]) swap(AA[parent],AA[now]);
        else break;
        now = parent;
        parent = now>>1;
    }
    ++now;
}
void PQ :: pop()
{
    int parent, child;
    AA[1] = AA[indx-- -1];
    parent = 1;
    child = parent<<1;
    while(child<indx)
    {
        if (child+1<indx && V_cost[AA[child]]>V_cost[AA[child+1]]) ++child;
        if (V_cost[AA[child]]<=V_cost[AA[parent]])
        {
            swap(AA[child],AA[parent]);
            parent = child;
        }
        else break;
        child = parent<<1;
    }
}
PQ pq;
int dijkstra(int source, int dest, int N)
{
    int n,now,i,j;
    for (n=1; n<=N; ++n)
    {
        now = pq.front();
        //printf("\t%d %d %d\n",now,V_cost[now],pq.indx);
        //printf("\t\t"); pq.print();
        pq.pop();
        //printf("\t\t"); pq.print();
        if (now == dest) break;
        for (i=1; i<nl[now]; ++i) V_cost[ad_list[now][i].node] = MINI(V_cost[ad_list[now][i].node], V_cost[now]+ad_list[now][i].cost);
        //for (j=1; j<=N; ++j) printf("%d %d, ",j,V_cost[j]);
        //puts("");
        //pq.print();
        //puts("");
    }
    return V_cost[dest];
}
int main()
{
    int i,N,E;
    int source,dest,cost;
    while(scanf("%d%d",&N,&E)!=EOF)
    {
        pq.indx = 1;
        for (i=1; i<=N; ++i) nl[i] = 1;
        for (i=1; i<=E; ++i)
        {
            scanf("%d%d%d",&source,&dest,&cost);
            ad_list[source][nl[source]].node = dest;
            ad_list[source][nl[source]].cost = cost;
            ++nl[source];
        }
        scanf("%d%d",&source,&dest);
        for (i=1; i<=N; ++i)
        {
            if (i!=source) V_cost[i] = MAXINT;
            else V_cost[i] = 0;
            pq.push(i);
        }
        sort_list(N);
        cost = dijkstra(source,dest,N);
        printf("%d\n",cost);
    }
    return 0;
}

/*
3 3
1 2 100
1 3 200
2 3 50
1 3
*/
