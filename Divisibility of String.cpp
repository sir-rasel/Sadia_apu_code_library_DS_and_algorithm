#include<stdio.h>
char num[100];
int main()
{
    char *i;
    int car,f;
    while(scanf("%s",num)!=EOF)
    {
        f=0;
        i=num;
        car=0;
        while(*i)
        {
            car= car*10 + (*i-'0');
            if (car/17) f=1;
            if (car/17 || (car/17==0 && f==1)) printf("%d",car/17);
            car = car%17;
            i++;
        }
        printf("  remainder : %d\n\n",car);
    }
    return 0;
}
