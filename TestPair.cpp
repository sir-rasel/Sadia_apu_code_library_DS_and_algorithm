#include<stdio.h>
#include<string.h>
#include<utility>
#include<set>
using namespace std;
set < pair <int, int> > S;
set < pair <int, int> > :: iterator is;
int main()
{
    S.clear();
    for (int i=0; i<10; ++i)
    {
        S.insert(make_pair((i+4)%5, i));
    }
    for (is = S.begin(); is != S.end(); ++is) printf("%d %d\n", (*is).first, (*is).second);
    pair <int, int> p,q;
    p.first = 3, p.second = 6;
    q = p;
    p.first = 4, p.second = 8;
    printf("%d %d\n", q.first, q.second);
    return 0;
}
