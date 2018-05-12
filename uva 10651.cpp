#include<stdio.h>
#define MAX 1<<12
int mark[MAX],ANS;
char str[15];
int GET(char str[15])
{
    int i,j, ret=0;
    for (i=0,j=11; j>=0; i++,j--)
    {
        if (str[j]=='o') ret = ret | (1<<i);
    }
    return ret;
}
int check(int n)
{
    int ret = 0;
    while(n)
    {
        if (n&1) ret++;
        n = n>>1;
    }
    return ret;
}
void insert(int n)
{
    int i,m;
    int take = check(n);
    if (take<ANS) ANS = take;
    for (i=1; i<12; i++)
    {
        if (n&(1<<i) && n&(1<<(i-1)))
        {
            if (i>1 && (n&(1<<(i-2)))==0)
            {
                m = n;
                m = m &=~ (1<<i);
                m = m &=~ (1<<i-1);
                m = m | (1<<i-2);
                if (mark[m]==0)
                {
                    mark[m] = 1;
                    insert(m);
                }
            }
            if (i<11 && (n&(1<<(i+1)))==0)
            {
                m = n;
                m = m &=~ (1<<i);
                m = m &=~ (1<<i-1);
                m = m | (1<<i+1);
                if (mark[m]==0)
                {
                    mark[m] = 1;
                    insert(m);
                }
            }
        }
    }
}
int main()
{
    int T,i,j,k,get;
    scanf("%d",&T);
    while(T--)
    {
        for (i=0; i<MAX; i++) mark[i]= 0;
        scanf("%s",str);
        ANS = 13;
        get = GET(str);
        mark[get] = 1;
        insert(get);
        printf("%d\n",ANS);
    }
    return 0;
}
