#include<stdio.h>
#include<conio.h>
int A[2][2]={{1, 1}, {1, 0}};
int B[2][2]={{1, 1}, {1, 0}};
int m;

void print_matr()
{
    int i,j;
    for (i=0; i<2; i++) 
    {
        for (j=0; j<2; j++) 
        printf("%d ",A[i][j]);
        printf("\n");
    }
    printf("\n");
    A[0][0]=1;
    A[0][1]=1;
    A[1][0]=1;
    A[1][1]=0;
}

void matr( int n, int m)
{
    if (n==1)
    {
        return;
    }
    int B[2][2]={{1, 1}, {1, 0}};
    if (n%2)
    {
        A[0][0]+=A[0][1];
        A[1][0]+=A[1][1];
        A[1][1]= A[1][0]-A[1][1];
        A[0][0]= A[0][0]%m;
        A[0][1]= A[0][0]%m;
        A[1][0]= A[0][0]%m;
        A[1][1]= A[0][0]%m;
        matr(n/2, m);
    }
    else
    {
        matr(n/2, m);
    }

}
int main()
{
    int i,j,n;
    for (i=0; i<2; i++) 
    {
        for (j=0; j<2; j++) 
        printf("%d ",A[i][j]);
        printf("\n\n");
    }
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        matr(n,m);
    }
    print_matr();
            
    getch();
    return 0;
}
