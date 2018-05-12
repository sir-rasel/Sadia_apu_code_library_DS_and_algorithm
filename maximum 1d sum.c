#include<stdio.h>
int main()
{
    int i,n,input, sumin,highest,start,end,START,END,t,T;
    scanf("%d",&T);
    for (t=1;t<=T;t++)
    {
        scanf("%d",&n);
        if (t>1) printf("\n");
        start=START=1;
        end=END=0;
        sumin = 0;
        highest=-32767;
        for (i=1;i<=n;i++)
        {
            scanf("%d",&input);
            if (sumin<0)
            {
                start=i;
                sumin=0;
                end=i-1;
            }
            sumin += input;
            end++;
            if (sumin>highest)
            {
                START=start;
                END=end;
                highest = sumin;
            }
        }
        printf("Case %d:\n%d %d %d\n",t,highest,START,END);
    }
    return 0;
}
