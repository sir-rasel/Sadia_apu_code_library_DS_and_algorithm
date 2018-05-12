#include<stdio.h>
#include<math.h>

int main()
{
    long grid, skew;
    double height, width;
    double l1,l2,h;
    long x,L;
    long b1,b2;
    long res,f;
    long skew1, skew2, grid1, grid2;
    while(scanf("%lf%lf",&height,&width)!=EOF)
    {
        f=0;
        if (height<1 || width<1) 
        {
            printf("0 grid\n");
            continue;
        }
        x = 1+((height-1)*(2.0)/sqrt(3.0));
        b1= height;
        b2= width;
        grid1= b1*b2;
        L= (long) width;
        l1= L;
        l2= L + 0.5; 
        
        if (l2<=width) 
        {
            skew1= L*x;
        }
        else
        {
            if (x%2==0) 
            {
                skew1= (x/2)*(2*L-1);
            }
            else 
            {
                skew1= (x/2+1)*L + (x/2)*(L-1);
            }
        }
        l1=height;
        height=width;
        width=l1;
        x = 1+((height-1)*(2.0)/sqrt(3.0));
        b1= height;
        b2= width;
        grid2= b1*b2;
        L= (long) width;
        l1= L;
        l2= L + 0.5;
        
        if (l2<=width) 
        {
            skew2= L*x;
        }
        else
        {
            if (x%2==0) 
            {
                skew2= (x/2)*(2*L-1);
            }
            else 
            {
                skew2= (x/2+1)*L + (x/2)*(L-1);
            }
        }
        if (grid1>grid2) grid=grid1;
        else grid=grid2;
        if (skew1>skew2) skew=skew1;
        else skew=skew2;
        if (grid>=skew) printf("%ld grid\n",grid);
        else printf("%ld skew\n",skew);
    }
    return 0;
}
        
                
            
