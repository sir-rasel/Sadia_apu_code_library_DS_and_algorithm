#include<stdio.h>
char board[6][6];
int n;
int ulres;
int check( int X, int Y)
{
    int i;
    for (i=X-1; i>=0; i--)
    {
        if (board[i][Y]=='X') break;
        if (board[i][Y]=='*') return 0;
    }
    for (i=Y-1;i>=0;i--)
    {
        if (board[X][i]=='X') break;
        if (board[X][i]=='*') return 0;
    }
    return 1;
}
void bktk( int r,int c,int res)
{
    if (r==n)
    {
        if (res>ulres) ulres=res;
        return;
    }
    int i,f=0;
    for (i=c; i<n; i++)
    {
        if (board[r][i]=='.' && check(r,i))
        {
            f=1;
            board[r][i]='*';
            if (i==n-1) bktk(r+1,0,res+1);
            else bktk(r,i,res+1);
            board[r][i]='.';
        }
    }
    if (f==0) bktk(r+1,0,res);
}
int main()
{
    int i;
    while(scanf("%d",&n) && n)
    {
        getchar();
        ulres=0;
        for (i=0; i<n; i++) scanf("%s",board[i]);
        bktk(0,0,0);
        printf("%d\n",ulres);
    }
    return 0;
}
