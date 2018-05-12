#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define MINI(a,b) ((a)<(b)?(a):(b))
#define MAXN 50003
#define MAXL 30
int n,stp,mv;
int sum[MAXN],cnt[MAXN],rrank[MAXL][MAXN], suf[MAXN], suffix[MAXN], tmp[MAXN],lcps[MAXN];
char str[MAXN];
int LCP(int u,int v)
{
    int ret=0,i;
    for(i = stp; i >= 0 && u<n && v<n; i--)
    {
        if(rrank[i][u]==rrank[i][v])
        {
            ret += 1<<i;
            u += 1<<i;
            v += 1<<i;
        }
    }
    return ret;
}
bool equal(int u,int v)
{
    if(!stp) return str[u]==str[v];
    if(rrank[stp-1][u]!=rrank[stp-1][v]) return false;
    int a = u + mv < n ? rrank[stp-1][u+mv] : -1;
    int b = v + mv < n ? rrank[stp-1][v+mv] : -1;
    return a == b ;
}
void update()
{
    int i;
    for(i=0; i<n; ++i) sum[i] = 0;
    int rnk = 0;
    for(i=0; i<n; i++)
    {
        suffix[i] = tmp[i];
        if(i && !equal(suffix[i],suffix[i-1]))
        {
            rrank[stp][suffix[i]]= ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else rrank[stp][suffix[i]] = rnk;
        ++sum[rnk+1];
    }
}
void Sort()
{
    int i;
    for(i=0; i<n; ++i) cnt[i] = 0;
    memset(tmp, -1, sizeof tmp);
    for(i=0; i<mv; ++i)
    {
        int idx = rrank[stp-1][n-i-1];
        int x = sum[idx];
        tmp[x+cnt[idx]] = n-i-1;
        ++cnt[idx];
    }
    for(i=0; i<n; ++i)
    {
        int idx = suffix[i] - mv;
        if(idx<0) continue;
        idx = rrank[stp-1][idx];
        int x = sum[idx];
        tmp[x+cnt[idx]] = suffix[i] - mv;
        ++cnt[idx];
    }
    update();
}

bool cmp(const int &a,const int &b)
{
    return str[a]<str[b];
}
void buildSuffixArray(int nn)
{
    n = nn;
    int i;
    for(i=0; i<n; i++) tmp[i] = i;
    sort(tmp,tmp+n,cmp);
    stp = 0;
    update();
    ++stp;
    for(mv=1; mv<n; mv<<=1)
    {
        Sort();
        stp++;
    }
    stp--;
}
bool cmp2(int x, int y)
{
    int l = LCP(x,y);
    return (str[x+l] < str[y+l]);
}
int main()
{
    int i,len;
    long long ans,temp;
    while(scanf("%s", str) != EOF)
    {
        len = strlen(str);
        for (i=len-1; i>=0; --i) suf[i] = i;
        buildSuffixArray(len);
        sort(suf, suf+len, cmp2);
        for (i=0; i<len; ++i) printf("%d " , suf[i]); puts("");
        lcps[0] = 0;
        for (i=1; i<len; ++i) lcps[i] = LCP(suf[i-1], suf[i]);
        ans = 0;
        for (i=0; i<len; ++i)
        {
            //temp = (long long) MINI(len-suf[i], found[suf[i]]-suf[i]+lensub-1) - lcps[i];
            if (temp>0) ans += (long long) temp;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
