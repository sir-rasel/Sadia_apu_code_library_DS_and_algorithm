#include<bits/stdc++.h>
using namespace std;
#define MAXN 250006
#define SQN 506
#define MAXV 50000
int array[MAXN], sqn, msqn, BIT[SQN][MAXV+1];
void update(int sq, int V, int u)
{
    int val;
    while (sq <= msqn)
    {
        val = V;
        while (val <= MAXV)
        {
            BIT[sq][val] += u;
            val += val & -val;
        }
        sq += sq & -sq;
    }
}
int queryBIT(int sq, int V)
{
    int ret = 0, val;
    while (sq > 0)
    {
        val = V;
        while (val > 0)
        {
            ret += BIT[sq][val];
            val -= val & -val;
        }
        sq -= sq & -sq;
    }
    return ret;
}
int query(int idx, int val) /// how many in (index <= idx, with value <= val)
{
    int sq = (idx-1) / sqn;
    int ret = queryBIT(sq, val);
    int i;
    for (i=sq*sqn+1; i<=idx; ++i) ret += (array[i] <= val);
    return ret;
}
int cntinv(int N, int idx)
{
    return query(idx,MAXV) - query(idx,array[idx]) + query(N,array[idx]-1) - query(idx,array[idx]-1);
}
int main()
{
    int N,Q,i,idx,val,msq;
    long long ans;
    scanf("%d", &N);
    sqn = sqrt((double) N);
    msqn = (N-1) / sqn + 1;
    for (i=1; i<=N; ++i)
    {
        scanf("%d", &array[i]);
        update((i-1)/sqn+1, array[i], 1);
    }
    ans = 0;
    for (i=1; i<=N; ++i) ans += cntinv(N,i);
    ans /= 2;
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%d %d", &idx, &val);
        ans -= cntinv(N,idx);
        update((idx-1)/sqn+1, array[idx], -1);
        array[idx] = val;
        update((idx-1)/sqn+1, array[idx], +1);
        ans += cntinv(N,idx);
        printf("%lld\n", ans);
    }
    return 0;
}
