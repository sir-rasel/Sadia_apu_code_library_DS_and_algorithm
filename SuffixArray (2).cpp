#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;   /* repetition finder*/
#define MAXN  1003
#define MAXLG 30
char A[MAXN];
struct entry
{
    int nr [2], p;
} L[MAXN];
int P[MAXLG][MAXN], N, i , stp, cnt;
int cmp(struct entry a, struct entry b)
{
    return a .nr[0] == b.nr[0] ? (a .nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}
int buildSuffixArray(int N)
{
    for(i=0; i<N; ++i) P[0][i] = A[i]-'A';
    for(stp=1, cnt=1; (cnt>>1)<N; ++stp, cnt<<=1)
    {
        for (i=0; i<N; ++i)
        {
            L[i].nr[0] = P[stp-1][i];
            L[i].nr[1] = i + cnt<N ? P [stp - 1][i + cnt] : -1;
            L[i].p = i;
        }
        sort(L, L + N, cmp);
        for (i=0; i<N; ++i)
             P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
     }
     stp--;
}
int LCP(int x, int y)
{
    int i,l,ret=0;
    if (x==y) return N-x;
    for (l=stp; l>=0 && x<N && y<N; --l)
    {
        if (P[l][x] == P[l][y])
        {
            x += (1<<l);
            y += (1<<l);
            ret += (1<<l);
        }
    }
    return ret;
}
int modifiedStrcmp(char *s1, char *s2, int len)
{
    while(len--)
    {
        if (*s1 < *s2) return 1;
        if (*s1 > *s2) return 0;
        ++s1, ++s2;
    }
    return 2;
}
int main(void)
{
    int i,j,T;
    int indx, lcp, freq;
    int l,f,temp,x;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", A);
        N = strlen(A);
        buildSuffixArray(N);
        indx = lcp = freq = -1;
        for (i=0; i<N; ++i)
        {
            f = 1;
            l = 0;
            for (j=i+1; j<N; ++j)
            {
                temp = LCP(i,j);
                if (temp==l) ++f;
                else if (temp>l)
                {
                    l = temp;
                    f = 2;
                }
            }
            if (l>0)
            {
                if (l>lcp)
                {
                    indx = i;
                    lcp = l;
                    freq = f;
                    continue;
                }
                if (l==lcp) x = modifiedStrcmp(&A[i],&A[indx],lcp);
                else x = -1;
                if (l==lcp && x==1)
                {
                    indx = i;
                    lcp = l;
                    freq = f;
                }
                /*else if (l==lcp && x==2) ++freq;*/
            }
        }
        if (indx == -1) puts("No repetitions found!");
        else
        {
            for (i=indx, j=0; j<lcp; ++i,++j) printf("%c", A[i]);
            printf(" %d\n", freq);
        }
    }
    return 0 ;
}
