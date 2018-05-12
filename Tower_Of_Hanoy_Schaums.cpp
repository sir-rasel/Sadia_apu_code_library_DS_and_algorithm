#include<stdio.h>
void transfer ( int n, char from, char to, char temp)
{
    if (!n) return;
    transfer(n-1,from,temp,to);
    printf("Move disk %d from %c to %c\n",n,from,to);
    transfer(n-1,temp,to,from);
    printf("\n");
    return;
}
int main()
{
    int n;
    printf("disk number : ");
    scanf("%d",&n);
    transfer(n,'L','R','C');
    return 0;
}
