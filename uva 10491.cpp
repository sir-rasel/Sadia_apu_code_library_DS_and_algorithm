#include<stdio.h>

int main()
{
    double L,W,P;
    double res;
    
    while(scanf("%lf%lf%lf",&L,&W,&P)!=EOF)
    {
        res= (W*(L+W-1)) / (2*W*L+L*L-L*P-W*P-W+W*W-L);
        printf("%.5lf\n",res);
    }
    return 0;
}
