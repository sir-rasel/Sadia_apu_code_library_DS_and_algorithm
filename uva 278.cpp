#include<stdio.h>

int knight(int m, int n)
{
    if (m<n)
    {
        m+=n;
        n=m-n;
        m-=n;
    }
    if (n==1) return m;
    else return (m*n+1)/2;
}

int rook_nd_queen( int m, int n)
{
    if (n<m) return n;
    else return m;
}

int king(int m, int n)
{
    if (m%2 && n%2) return ((m+1)*(n+1))/4;
    else if (m%2) return (n*(m+1))/4;
    else if (n%2) return (m*(n+1))/4;
    else return (m*n+2)/4;
}

int main()
{
    int m,n;
    char ch[2];
    int t;
    int res;
    scanf("%d",&t);
    ch[0]=getchar();
    while(t)
    {
        scanf("%s%d%d",ch,&m,&n);
        if (ch[0]=='K') res=king(m,n);
        else if (ch[0]=='Q' || ch[0]=='r') res=rook_nd_queen(m,n);
        else if (ch[0]=='k') res=knight(m,n);
        printf("%d\n",res);
        t--;
        ch[0]=getchar();
    }
    return 0;
}



