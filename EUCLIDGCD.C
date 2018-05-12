#include<stdio.h>
long long unsigned gcd(long long unsigned m, long long unsigned n)
{
	 long long unsigned temp;
	 if(m<n)
	 {
		temp=m;
		m=n;
		n=temp;
	 }
	 while(n)
	 {
		temp=m;
		m=n;
		n=temp%n;
	 }
	 return m;
}
int main()
{
	long long unsigned m,n;
	int count=0;
	scanf("%I64u%I64u", &m, &n);
	while(m&&n)
	{
		printf("Case #%d: %I64u\n",++count,gcd(m,n));
		scanf("%I64u%I64u", &m, &n);
	}
	return 0;
}
