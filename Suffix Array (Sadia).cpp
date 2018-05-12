#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
#define MAXLEN 100000
char str[MAXLEN+3];
int SuffixArray[(MAXLEN<<1)+3][20];
int charMark[26];
struct node
{
    int first, second, indx;
    node(int f, int s, int i) {first=f, second=s, indx=i;}
};
bool cmp(node a, node b)
{
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}
vector < vector <node> > V(MAXLEN+3);
int LEN,lg;
void FindSuffixArray(char *str)
{
    int i,j,k,lim,nxt,suffind,first,second;
    memset(SuffixArray, 0, sizeof(SuffixArray));
    memset(charMark, 0, sizeof(charMark));
    for (i=0; str[i]; ++i)
    {
        str[i] -= 'A';
        charMark[str[i]] = 1;
    }
    LEN = i;
    j = 1;
    for (i=0; i<26; ++i)
    {
        if (charMark[i]) charMark[i] = j++;
    }
    suffind = j-1;
    for (i=0; i<LEN; ++i) SuffixArray[i][0] = charMark[str[i]];
    /*for (i=0; i<LEN; ++i) printf("%d ", SuffixArray[i]);
    puts("");*/
    lim = ceil(log10(LEN)/log10(2.0));
    for (lg=nxt=1; lg<=lim; ++lg, nxt<<=1)
    {
        for (j=0; j<=suffind; ++j) V[j].clear();
        for (i=0; i<LEN; ++i)
        {
            V[SuffixArray[i][lg-1]].push_back(node(SuffixArray[i][lg-1],SuffixArray[i+nxt][lg-1],i));
        }
        for (j=0; j<=suffind; ++j) sort(V[j].begin(), V[j].end(), cmp);
        k = 0;
        first = second = -1;
        for (i=0; i<=suffind; ++i)
        {
            for (j=0; j<V[i].size(); ++j)
            {
                if (first != V[i][j].first || second != V[i][j].second)
                {
                    first = V[i][j].first;
                    second = V[i][j].second;
                    ++k;
                }
                SuffixArray[V[i][j].indx][lg] = k;
            }
        }
        suffind = k;
    }
    --lg;
    for (i=0; i<LEN; ++i) --SuffixArray[i][lg];
}
int LCP(int x, int y)
{
    int i,l,ret=0;
    if (x==y) return LEN-x;
    for (l=lg; l>=0 && x<LEN && y<LEN; --l)
    {
        if (SuffixArray[x][l] == SuffixArray[y][l])
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
int main()
{
    int i,j,T;
    int indx, lcp, freq;
    int l,f,temp,x;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", str);
        FindSuffixArray(str);
        indx = lcp = freq = -1;
        for (i=0; i<LEN; ++i)
        {
            f = 1;
            l = 0;
            for (j=i+1; j<LEN; ++j)
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
                if (l==lcp) x = modifiedStrcmp(&str[i],&str[indx],lcp);
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
            for (i=indx, j=0; j<lcp; ++i,++j) printf("%c", str[i]+'A');
            printf(" %d\n", freq);
        }
    }
    return 0;
}
