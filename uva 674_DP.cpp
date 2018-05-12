#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MAX 8000
long long res[MAX]={0};
int coins[5]={1,5,10,25,50};

int main()
{
    int i,j,c;
    res[0]=1;
    for (i=0; i<5; i++)
    {
        c= coins[i];
        for (j=c; j<MAX; j++)
        {
            res[j]+=res[j-c];
        }
    }
    float n;

    while(scanf("%d",&c)!=EOF)
    {
        printf("%lld\n",res[c]);
    }
    return 0;
}
