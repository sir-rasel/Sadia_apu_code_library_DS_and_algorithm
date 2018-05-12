#include<stdio.h>
#include<algorithm>
using namespace std;
struct HW
{
    int day;
    int pen;
} hw[1003];
bool cmp(HW a, HW b)
{
    if (b.pen!=a.pen) return (b.pen<a.pen);
    else return b.day>a.day;
}
int arr[1003];
int main()
{
    int t,n,i,penalty,j,big;
    scanf("%d",&t);
    while(t--)
    {
        big=0;
        scanf("%d",&n);
        for (i=0;i<n; i++)
        {
            scanf("%d",&hw[i].day);
            if (hw[i].day>big) big=hw[i].day;
        }
        for (i=0;i<n; i++) scanf("%d",&hw[i].pen);
        for (i=0;i<=big; i++) arr[i]=0;
        sort(hw,hw+n,cmp);
        /*for (i=0;i<n; i++) printf("%d ",hw[i].day);
        puts("");
        for (i=0;i<n; i++) printf("%d ",hw[i].pen);
        puts("");*/
        penalty=0;
        for (i=0; i<n; i++)
        {
            if (arr[hw[i].day]==0) arr[hw[i].day]=1;
            else
            {
                j=hw[i].day-1;
                while(j>=1)
                {
                    if (arr[j]==0)
                    {
                        arr[j]=1;
                        j=15000;
                        break;
                    }
                    j--;
                }
                if (j!=15000)
                {
                    //printf("\t%d\n",i);
                    penalty += hw[i].pen;
                }
            }
        }
        printf("%d\n",penalty);
    }
}
