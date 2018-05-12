#include<stdio.h>
#include<string.h>
char input[130];
char check[130];
int main()
{
    int T,i,start,end;
    scanf("%d",&T);
    input[0] = getchar();
    while(T--)
    {
        i=0;
        gets(input);
        if (!strlen(input))
        {
            printf("Yes\n");
            continue;
        }
        start=0;
        for (i=0;input[i];i++) check[i]=0;
        i=0;
        for (end=1; input[end]; end++)
        {
            if (input[end]==')')
            {
                if (input[start]!='(')
                {
                    i=1;
                    break;
                }
                else if (check[start]!=1)
                {
                    check[start]=1;
                    check[end]=1;
                    while(start && check[start]==1) start--;
                }
            }
            else if (input[end]== ']')
            {
                if (input[start]!='[')
                {
                    i=1;
                    break;
                }
                else if (check[start]!=1)
                {
                    check[start]=1;
                    check[end]=1;
                    while(start && check[start]==1) start--;                }
            }
            else start = end;
        }
        for (start=0; input[start]; start++)
        {
            if (check[start]==0)
            {
                i=1;
                break;
            }
        }
        if (i) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}
