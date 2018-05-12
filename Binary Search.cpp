#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
    int array[20]={0};
    int n,x,i,m;
    int *start, *end, *mid;
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        scanf("%d",&array[i]);
    }
    sort(array,array+n);
    m=n;
    while(scanf("%d",&x)!=EOF)
    {
        n=m;
        --n;
        start=array;
        end=array+n;
        n/=2;
        mid=start+n;
        while(mid!=end)
        {
            if (*mid==x) break;
            else if (*mid<x)
            {
                start = mid+1;
                n= end-start;
                n/=2;
                mid= start+n;
            }
            else if (*mid>x)
            {
                end= mid-1;
                n= end-start;
                n/=2;
                mid= start+n;
            }
        }
        if (*mid==x) printf("%d\n",mid-array);
        else printf("not found\n");
    }
    return 0;
}
