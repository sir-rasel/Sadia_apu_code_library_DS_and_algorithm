#include<stdio.h>
long power(long a, long b){
    long c,res=1;
    for ( c=1; c<=b; c++) res*=a;
    return res;
}
int main()
{
    long temp[9]={0};
    long a,lim=0,b,n,m,d,c;
    for ( a=1; a<9; a++) temp[a]= temp[a-1] + 9* power(10,a-1)* a;
    while(scanf("%ld", &n) !=EOF){
        for ( a=1; temp[a]<=n; a++);
        a--;
        m=n-temp[a];
        d=m/(a+1);
        for ( b=power(10,a),c=1;c<=d ; b++,c++);
        d=m%(a+1);
        if (!d) b--;
        else{
            c= (a+1)-d;
            for(d=1; d<=c; d++) b/=10;
        }
        printf("%ld\n", b%10);
    }
    return 0;
}
            
        
