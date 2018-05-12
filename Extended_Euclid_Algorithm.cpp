#include<stdio.h>
int GCD(int a, int b)
{
    if (!b) return a;
    return GCD(b, a%b);
}
void ext_euclid(int a, int b, int &d, int &x, int &y)
{
    if (b==0)
    {
        d = a, x = 1, y = 0;
        return;
    }
    int x_, y_;
    ext_euclid(b, a%b, d, x_, y_);
    x = y_;
    y = x_ - y_ * ((int) a/b);
}
int main()
{
    int d,x,y,a,b;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        ext_euclid(a,b,d,x,y);
        printf("%d %d %d\n",d,x,y);
    }
    return 0;
}
