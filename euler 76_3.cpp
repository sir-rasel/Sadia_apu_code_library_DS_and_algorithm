#include<stdio.h>
long x[1001];
long res[1001],bres[1001];
long conds[100000],c,condp[100000];
long k;
long s,t;
long ans=0;
   
void sum(long cond, long p, long r)
{
    long j,n;
    if (cond>s) return;
    if (cond==s) 
    {
        n=0;
        for (j=1; j<r; j++) if (bres[j]!=res[j]) 
        {
            n=1;
            break;
        }
        if (n)
        {
            for (j=1; j<r; j++) 
            {
                printf("%ld ",res[j]);
                bres[j]=res[j];
            }
            printf("\n");
        }
        return;
    }
    cond+=x[p];
    conds[c]=cond;
    condp[c++]=p;
    res[r++]=x[p];      
    for (n=p; n<k; n++) sum(cond,n,r);
    if (cond>=s) 
    {
        r--; 
        cond-=x[p];
        if (!cond) return;
        p++;
    }
    if (p==k) return;
}            
    
int main()
{
    long i,j,d;
    
    while(scanf("%ld",&s))
    {
        k=1;
        for (k=1,t=s-1;t>0;k++,t--)
        {
            x[k]=t;
        }   
        printf("Sums of %ld:\n",s);
        for (i=1; i<k; i++) 
        {
            c=1;
            sum(0,i,1);
        }
    }
    return 0;
}       
