#include<stdio.h>
#define MAXLEN 50000
long array[MAXLEN+3];
long binary_search(long N, long val)
{
    long low = 0, high = N;
    long mid;
    while(low <= high)
    {
        mid = (low+high)/2;
        if (array[mid]==val) return mid;
        if (array[mid]>val) high = mid-1;
        else low = mid+1;
    }
    return -1;
}
long lower_bound(long N, long x)
{
    long low = 0, high = N, mid;
    while(low<high)
    {
        mid = (low+high) / 2 + 1;
        if (array[mid]>=x) high = mid-1;
        else low = mid;
    }
    return low;
}
long upper_bound(long N, long x)
{
    long low = 1, high = N+1, mid;
    while(low<high)
    {
        mid = (low+high) / 2;
        if (array[mid]>x) high = mid;
        else low = mid+1;
    }
    return high;
}
int main()
{
    long i,N,Q,j;
    while(scanf("%ld",&N)!=EOF)
    {
        for (i=1; i<=N; ++i) scanf("%ld",&array[i]);
        array[0] = array[i-1];
        array[N+1] = array[N]+1;
        scanf("%ld",&Q);
        while(Q--)
        {
            scanf("%ld",&i);
            j = lower_bound(N,i);
            if (j<1 || j>N) printf("X ");
            else printf("%ld ",array[j]);
            j = upper_bound(N,i);
            if (j<1 || j>N) printf("X\n");
            else printf("%ld\n",array[j]);
        }
    }
    return 0;
}
