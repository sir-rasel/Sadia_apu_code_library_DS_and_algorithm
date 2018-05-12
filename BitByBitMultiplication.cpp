long long multiply(long long a, long long b)
{
    long long ret = 0;
    int i,j;
    a %= MOD;
    b %= MOD;
    for (i=0; i<64; ++i)
    {
        if (((1LL)<<i) > a) break;
        if (((1LL)<<i) & a)
        {
            ret = (ret + b);
            if (ret >= MOD) ret -= MOD;
        }
        b <<= 1;
        if (b >= MOD) b -= MOD;
    }
    return ret;
}
long long bigmod(long long a, long long k)
{
    if (k == 0) return 1LL;
    if (k % 2) return multiply(a,bigmod(a,k-1));
    long long ret = bigmod(a, k/2);
    return multiply(ret,ret);
}
