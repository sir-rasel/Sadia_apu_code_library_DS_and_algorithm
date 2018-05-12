#include<stdio.h>
#include<conio.h>
unsigned long long i,h;
unsigned long long array[100]={0},fibo[100]={0},res[100]={0};
unsigned long long pain( unsigned long long n)
{
    printf("n %llu\n",n);
    for (h=1; h<83; h++) if (fibo[h]>n) break;
    h--; 
    if (n==fibo[h]) return res[h-1];
    printf("h %llu\n",fibo[h]);
    return res[h-1]+n-fibo[h]+ pain(n-fibo[h]); //res[h-1] +1 + n - fibo[h] + pain(n - fibo[h]) 
}
int main()
{
    unsigned long long j=1,sum=0, i;
    unsigned long long n=1;
    for (i=0; i<17; i++) n*=10;
//    scanf("%lld",&n);
    array[1]=1;
    array[2]=1;
    array[3]=3;
    fibo[1]=1;
    fibo[2]=2;
    fibo[3]=3;
    res[1]=1;
    res[2]=2;
    res[3]=5;
    for (i=4; i<83; i++)
    {
        for (j=i-2; j>0; j--) array[i]+=array[j];
        fibo[i]=fibo[i-1]+fibo[i-2];
        array[i]+=fibo[i-1];
        res[i]=res[i-1]+array[i];
        printf("%llu %llu %llu\n",i,array[i],res[i]);
    }
    for (i=1; fibo[i]<n; i++);
    i--;
    printf("*********************\n");
    sum=pain(n);
    printf("%llu\n",sum);
    getch();
    return 0;
}

