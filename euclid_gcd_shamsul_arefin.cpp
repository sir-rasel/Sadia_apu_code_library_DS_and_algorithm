#include<stdio.h>
int GCD(int a,int b) {
  while (b > 0) {
    a = a % b;
    a ^= b;    b ^= a;    a ^= b;  }  return a;
}
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)!=EOF) printf("%d\n",GCD(a,b));
    return 0;
}
