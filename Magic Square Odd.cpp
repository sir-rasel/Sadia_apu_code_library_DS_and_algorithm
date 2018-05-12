#include<stdio.h>
#include<conio.h>
int main()
{
             int a[20][20],r,c,br,bc,k,n;
             printf("Enter the Order of Magic Square(Odd): ");
             scanf("%d",&n);
             for(r=0;r<n;r++)
                          for(c=0;c<n;c++)
                                       a[r][c]=0;
             r=0;
             c=n/2;
             for(k=1;k<=n*n;k++)
             {
                          a[r][c]=k;
                          br=r;bc=c;
                          r=(r-1);
                          if(r<0)
                          				r=n-1;
                          c=(c+1)%n;
                          if(a[r][c]!=0)
                          {
                                       c=bc;
                                       r=br-1;
                                       if(r<0)r=n-1;
                          }
             }
             printf("The Magic Square...\n");
             for(r=0;r<n;r++)
             {
                          for(c=0;c<n;c++)
                                       printf("%4d",a[r][c]);
                          printf("\n");
             }
             getch();
             return 0;
}
