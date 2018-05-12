#define MAXP 106
char valid[27];
unsigned long long pw[MAXP];
string print(int k, int d, unsigned long long n)
{
    //printf("%d %d %llu\n", k, d, n);
    string ans = "";
    int i,j;
    j = d;
    while(j > 0)
    {
        for (i=0; i<k; ++i)
        {
            if ((i+1)*pw[j-1] >= n) break;
        }
        n -= i*pw[j-1];
        ans = ans + valid[i];
        --j;
    }
    return ans;
}
string gen(int k, unsigned long long n)
{
    int l,i;
    pw[0] = 1;
    for (i=1; i<MAXP; ++i) pw[i] = pw[i-1] * (unsigned long long) k;
    for (l=1; l<MAXP; ++l)
    {
        if (pw[l] >= n) break;
        if (pw[l] == 0) break;
        n -= pw[l];
    }
    return print(k,l,n);
}
