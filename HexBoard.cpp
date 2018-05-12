#include<stdio.h>
void draw(int n)
{
    int i,j,f=0;
    int hor_mark=2*n-1;
    int ver_mark=1,stand=-1;
    for (i=0; i<hor_mark; i++) printf(" ");
    printf("_\n");
    ver_mark++;
    while(ver_mark<=4*n-1)
    {
        if (f==0) hor_mark-=2;
        else if (f==2) hor_mark+=2;
        for (i=0; i<hor_mark; i++) printf(" ");
        if (stand==2*n) printf("  ");
        if (ver_mark==n+1)
        {
            f=1;
            stand++;
        }
        if (stand>=0 && stand<2*n)
        {
            if (stand%2==0)
            {
                printf("/ ");
                for (j=1;j<n;j++)
                {
                    printf("\\_/");
                    printf(" ");
                }
                printf("\\");
            }
            else
            {
                for (j=1; j<n; j++) printf("\\_/ ");
                printf("\\");
                printf("_/");
            }
            stand++;
        }
        else if (stand==2*n)
        {
            stand++;
            if (hor_mark<0) hor_mark+=3;
            f=2;
        }
        if (f==0)
        {
            for (j=1; j<ver_mark; j++) printf("_/ \\");
            printf("_");
        }
        else if (f==2)
        {
            printf("\\_/");
            for (i=ver_mark; i<4*n-1; i++) printf(" \\_/");
        }
        ver_mark++;
        printf("\n");
    }
}
int main()
{
    int n;
    while(scanf("%d",&n) && n!=-1)
    {
        draw(n);
        printf("***\n");
    }
    return 0;
}


