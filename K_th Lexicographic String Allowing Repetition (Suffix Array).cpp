// K'th Lexicographic String Allowing Repetition (Suffix Array)
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define INF 2147483647
#define MAXN 100006
#define MAXL 20
int n ,stp,mv,suffix[MAXN],tmp[MAXN];
int sum[MAXN], cnt[MAXN], Rank[MAXL][MAXN];
char str[MAXN];
int suf[MAXN];
int LCP(int u,int v)
{
    int ret=0,i;
    for(i = stp; i >= 0 && u<n && v<n; i--)
    {
        if(Rank[i][u]==Rank[i][v])
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
    if(!stp)return str[u]==str[v];
    if(Rank[stp-1][u]!=Rank[stp-1][v]) return false;
    int a = u + mv < n ? Rank[stp-1][u+mv] : -1;
    int b = v + mv < n ? Rank[stp-1][v+mv] : -1;
    return a == b ;
}
void update()
{
    int i;
    for(i = 0;i < n; i ++) sum[ i ] = 0;
    int rnk = 0;
    for(i = 0;i < n;i++)
    {
        suffix[ i ] = tmp[ i ];
        if( i&&!equal(suffix[i],suffix[i-1]))
        {
            Rank[stp][suffix[i]]=++rnk;
            sum[rnk+1]=sum[rnk];
        }
        else Rank[stp][suffix[i]]=rnk;
        sum[rnk+1]++;
    }
}
void Sort()
{
    int i;
    for(i = 0; i < n; i ++ ) cnt[ i ] = 0;
    memset(tmp,-1,sizeof tmp);
    for(i = 0 ; i < mv; i ++)
    {
        int idx = Rank[ stp - 1 ][ n-i-1 ];
        int x = sum[ idx ];
        tmp[ x + cnt[ idx ] ] = n-i-1;
        cnt[ idx ]++;
    }
    for(i = 0;i < n; i ++ )
    {
        int idx = suffix[ i ] - mv;
        if(idx<0)continue;
        idx = Rank[stp-1][idx];
        int x = sum[ idx ];
        tmp[ x + cnt[ idx ] ] = suffix[ i ] - mv;
        cnt[idx]++;
    }
    update();
}

bool cmp(const int &a,const int &b)
{
    return str[a]<str[b];
}
void buildSuffixArray()
{
    int i;
    for(i=0; i<n;i++) tmp[i] = i;
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
int search(int n, int idx, int len)
{
    int low = idx, high = n-1, mid, l;
    while(low < high)
    {
        mid = (low + high + 1) / 2;
        l = LCP(suf[idx],suf[mid]);
        if (l < len) high = mid-1;
        else if (l > len) low = mid+1;
        else low = mid;
    }
    return (high - idx + 1);
}
int KK;
int find(int n, int idx, int start)
{
    for (++start; start <= n-suf[idx]; ++start)
    {
        KK -= search(n,idx,start);
        if (KK<=0) return start;
    }
    return -1;
}
int main()
{
    int i,j,Q,ans,len,l;
    while(scanf("%s %d", str, &KK) != EOF)
    {
        n = strlen(str);
        buildSuffixArray();
        for (i=0; i<n; ++i) suf[i] = i;
        sort(suf, suf+n, cmp2);
        //for (i=0; i<n; ++i) printf("%d ", suf[i]); puts(""); //suf[i] = where i'th lexicographic suffix begins from
        l = 0;
        for (i=0; i<n; ++i)
        {
            len = find(n,i,l);
            if (len != -1) break;
            l = LCP(suf[i], suf[i+1]);
        }
        if (len != -1)
        {
            i = suf[i];
            while(len--) printf("%c", str[i++]);
            puts("");
        }
        else puts("No such line.");
    }
    return 0;
}
