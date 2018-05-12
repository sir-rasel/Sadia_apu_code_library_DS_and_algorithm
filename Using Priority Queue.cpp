#include<stdio.h>
#include<queue>
#include<vector>
#define MAX 100
using namespace std;
struct node
{
    int val;
} nodex;
class cmp
{
public:
    cmp() {}
    bool operator() (node &x, node &y)
    {
        return x.val > y.val;
    }
};
priority_queue <node,vector<node>, cmp> PQ;
int main()
{
    int o,x;
    while(scanf("%d",&o)!=EOF)
    {
        if (o==1)
        {
            scanf("%d",&x);
            nodex.val = x;
            PQ.push(nodex);
        }
        else
        {
            nodex = PQ.top();
            x = nodex.val;
            PQ.pop();
            printf("%d\n",x);
        }
    }
    return 0;
}
