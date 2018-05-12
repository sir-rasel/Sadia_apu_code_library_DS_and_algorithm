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
using namespace std;
#define MAXN 1506
int mod,modinv[MAXN];
int bigmod(int a, int k)
{
    if (k==0) return 1;
    if (k%2) return ((int) a*bigmod(a,k-1))%mod;
    int ret = bigmod(a, k/2);
    return (int) ((ret*ret) % mod);
}
void prep(int m)
{
    mod = m;
    int i;
    for (i=1; i<m; ++i) modinv[i] = bigmod(i,mod-2);
}
void normalize(vector < int > &V)
{
    while (V.size() && V[V.size()-1] == 0) V.pop_back();
}
class Polynomial
{
public:
    int sz;
    vector < int > coeff;
    Polynomial(vector < int > V) {normalize(V); coeff = V; sz = coeff.size();}
    bool operator< (const Polynomial &a) const
    {
        if (sz != a.sz) return sz < a.sz;
        int i;
        for (i=sz-1; i>=0; --i)
        {
            if (coeff[i] == a.coeff[i]) continue;
            return coeff[i] < a.coeff[i];
        }
        return false;
    }
    Polynomial operator% (const Polynomial &a) const
    {
        if (sz < a.sz) return *this;
        vector < int > b = coeff, q = a.coeff;
        int d,i,m;
        while (b.size() && b.size() >= q.size())
        {
            d = b.size() - q.size();
            i = q.size()-1;
            m = (modinv[q[i]%mod] * b[i+d]) % mod;
            for (; i>=0; --i) b[i+d] = (b[i+d] - q[i]*m + mod*mod) % mod;
            normalize(b); normalize(q);
        }
        return Polynomial(b);
    }
    void balance()
    {
        int i,m = modinv[coeff[coeff.size()-1]];
        if (m == 1) return;
        for (i=0; i<coeff.size(); ++i) coeff[i] = (coeff[i]*m)%mod;
    }
};
Polynomial gcd(Polynomial a, Polynomial b)
{
    if (b.sz == 0) return a;
    return gcd(b, a%b);
}
int main()
{
    vector < int > a,b;
    int T=0,P,n,x,i;
    while (scanf("%d", &P) != EOF && P)
    {
        prep(P);
        a.clear(), b.clear();
        scanf("%d", &n);
        for (i=0; i<=n; ++i)
        {
            scanf("%d", &x);
            a.push_back(x);
        }
        reverse(a.begin(), a.end());
        scanf("%d", &n);
        for (i=0; i<=n; ++i)
        {
            scanf("%d", &x);
            b.push_back(x);
        }
        reverse(b.begin(), b.end());
        Polynomial res = gcd(Polynomial(a),Polynomial(b));
        res.balance();
        printf("Case %d: %d", ++T, res.sz-1);
        for (i=res.sz-1; i>=0; --i) printf(" %d", res.coeff[i]);
        puts("");
    }
    return 0;
}
