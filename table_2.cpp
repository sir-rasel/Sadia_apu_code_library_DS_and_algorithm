#include<stdio.h>
#include<algorithm>
using namespace std;

struct TABLE
{
    int start,end;
} table[203];
int arr[203],n;
bool cmp ( TABLE a, TABLE b)
{
    if (a.start!=b.start) return b.start>a.start;
    else return b.end<a.end;
}
int call(int pos)
{
    for (int i=pos+1; i<n; i++)
    {
        if (table[i].start>=table[pos].end)
        {
            arr[i]=1;
        }
    }
    if (pos<n-1 && arr[pos+1]==0 && table[pos+1].start<=table[pos].end)
    {
        arr[pos+1] = 1;
        return 10+call(pos+1);
    }
    else return 10;
}
int main()
{
    int t,now,big;
    scanf("%d",&t);
    while(t--)
    {
        int i,temp;
        scanf("%d",&n);
        for (i=0; i<n; i++)
        {
            scanf("%d%d",&table[i].start,&table[i].end);
            if (table[i].start>table[i].end)
            {
                temp = table[i].start;
                table[i].start = table[i].end;
                table[i].end = temp;
            }
        }
        sort(table,table+n,cmp);
        for (i=0; i<n; i++) printf("\t%d %d\n",table[i].start, table[i].end);
        for (i=0; i<203; i++) arr[i]=0;
        big = 0;
        for (i=0; i<n; i++)
        {
            if (arr[i]==0)
            {
                arr[i]=1;
                now = call(i);
                if (now>big) big=now;
            }
        }
        printf("%d\n",big);
    }
}
