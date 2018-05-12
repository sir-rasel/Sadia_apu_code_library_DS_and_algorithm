#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<time.h>
#include<assert.h>
#include<iostream>
using namespace std;
#define MAXI(a,b) ((a)>(b)?(a):(b))
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MAXN 1000006
char str[MAXN], mstr[2*MAXN];
int dp[2*MAXN];
int manacher()
{
    int N,R,C,i,j,k,ans,mir;
    mstr[0] = '#';
    for (i=0,k=1; str[i]; ++i, k+=2)
    {
        mstr[k] = str[i];
        mstr[k+1] = '#';
    }
    N = k;
    mstr[N] = 0;
    C = R = dp[0] = 0;
    for (i=1; i<N-1; ++i)
    {
        mir = 2*C-i;
        dp[i] = (R>i) ? MINI(dp[mir], R-i) : 0;
        while (i-1-dp[i] >= 0 && mstr[i+1+dp[i]] == mstr[i-1-dp[i]]) ++dp[i];
        if (i+dp[i] > R) C = i, R = i + dp[i];
    }
    ans = 0;
    for (i=1; i<N-1; ++i)
    {
        if (dp[i] > ans)
        {
            ans = dp[i];
            C = i;
        }
    }
    //printf("%d ", C);
    int l = (C-ans)/2, r = l+ans-1;
    //for (k=l; k<=r; ++k) printf("%c", str[k]); puts("");
    return ans;
}
int main()
{
    int T = 0;
    while (scanf("%s", str) != EOF && strcmp(str,"END"))
    {
        printf("Case %d: %d\n", ++T, manacher());
    }
    return 0;
}
