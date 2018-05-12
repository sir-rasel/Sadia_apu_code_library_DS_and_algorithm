//xor sum
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
long long array[106];
bool cmp(long long x, long long y) {return x>y;}
void swap(long long &x, long long &y)
{
    long long z = x;
    x = y;
    y = z;
}
int main()
{
    int t,T;
    int N,i,j,k,p;
    long long ans;
    scanf("%d", &T);
    for (t=1; t<=T; ++t)
    {
        scanf("%d", &N);
        memset(array, 0, sizeof(array));
        for (i=0; i<N; ++i) scanf("%lld", &array[i]);
        sort(array, array+N, cmp);
        for (j=0; j<64 && (1LL<<j)<=array[0]; ++j); --j;
        p = j;
        ans = 0;
        for (i=0; j>=0; --j)
        {
            for (k=i; k<N; ++k)
            {
                if (array[k]&(1LL<<j)) break;
            }
            if (k==N) continue;
            swap(array[i], array[k]);
            for (k=i+1; k<N; ++k)
            {
                if (array[k]&(1LL<<j)) array[k] ^= array[i];
            }
            ++i;
        }
        for (i=0; i<N; ++i)
        {
            if ((ans^array[i])>ans) ans ^= array[i];
        }
        printf("Case %d: %lld\n", t, ans);
    }
    return 0;
}
