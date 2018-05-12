#include<stdio.h>
#include<string.h>
#define RANGE 10000
__int64 hnum[RANGE];
unsigned long long MAX=2;
int main()
{
    __int64 i2,i3,i5,i7,i,j=1;
    __int64 ans,ans2=1,ans3=1,ans5=1,ans7=1;
    for (i=1; i<=10; i++) MAX*=10;
    for (i2=0;i2<35;i2++)
    {
        for (i3=0;i3<22 && ans2*ans3<=MAX;i3++)
        {
            for (i5=0;i5<15 && ans2*ans3*ans5<=MAX; i5++)
            {
                for (i7=0;i7<13; i7++)
                {
                    ans= ans2*ans3*ans5*ans7;
                    if (ans>MAX || ans<0) break;
                    else hnum[j++]=ans;
                    ans7*=7;
                    if (ans7>MAX) break;
                }
                ans5*=5;
                ans7=1;
                if (ans5>MAX) break;
            }
            ans3*=3;
            ans5=1;
            if (ans3>MAX) break;
        }
        ans2*=2;
        ans3=1;
    }
    ans=j-1;
    for (i=1; i<=ans; i++)
    {
        for (j=i; j>1; j--)
        {
            if (hnum[j]<hnum[j-1])
            {
                i2= hnum[j];
                hnum[j]= hnum[j-1];
                hnum[j-1]=i2;
            }
        }
    }
    while(scanf("%I64d",&i) && i)
    {
        if (i%10==1 && i%100!=11) printf("The %I64dst humble number is %I64d.\n",i,hnum[i]);
        else if(i%10==2 && i%100!=12) printf("The %I64dnd humble number is %I64d.\n",i,hnum[i]);
        else if(i%10==3 && i%100!=13) printf("The %I64drd humble number is %I64d.\n",i,hnum[i]);
        else printf("The %I64dth humble number is %I64d.\n",i,hnum[i]);
    }
    return 0;
}
