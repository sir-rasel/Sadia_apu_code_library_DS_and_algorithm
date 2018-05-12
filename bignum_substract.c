#include<stdio.h>
void strrev( char *s, int len)
{
    int i;
    char ch;
    len--;
    for (i=0; i<=len/2; ++i)
    {
        ch= *(s+i);
        *(s+i) = *(s+len-i);
        *(s+len-i) = ch;
    }
    return;
}
int main()
{
    char num1[100], num2[100], ans[100];
    int len1,len2,i,j,car,sum,f;
    scanf("%s%s",num1,num2);
    for (len1=0;num1[len1];++len1);
    for (len2=0;num2[len2];++len2);
    f=0;
    strrev(num1,len1);
    strrev(num2,len2);
    for (i=0; num1[i]; ++i)
    {
        if (num2[i]==0) f=1;
        if (!f && num2[i]>48 && num1[i]<num2[i])
        {
            j=i;
            while(num1[j]==48)
            {
                num1[j]= '9';
                j++;
            }
            num1[j]--;
            num1[i]+=9;
        }
        if (f) num2[i]=48;
        ans[i]=num1[i]-num2[i]+48;
    }
    i--;
    for (; ans[i]=='0'; --i);
    ans[++i]=0;
    strrev(ans,i);
    printf("%s\n",ans);
    return 0;
}
