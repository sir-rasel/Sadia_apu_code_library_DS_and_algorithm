#include<stdio.h>
#include<algorithm>
using namespace std;
struct node
{
    int a;
    int b;
} array[100003];
bool cmp(node a, node b)
{
    return (b.b-b.a)<(a.b-a.a);
}

int main()
{
    int t;
    int a,n,v,i;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&v,&n);
        for (i=0; i<n; i++) scanf("%d%d",&array[i].a,&array[i].b);
        sort(array,array+n,cmp);
        a=0;
        for (i=0; i<n; i++)
        {
            if (array[i].b>v)
            {
                a=1;
                printf("No\n");
                break;
            }
            else v-=array[i].a;
        }

        if (a==0) printf("Yes\n");
    }
    return 0;
}
