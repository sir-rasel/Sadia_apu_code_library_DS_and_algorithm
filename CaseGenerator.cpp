#include<stdio.h>
#include<iostream>
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
int main()
{
    freopen("data.txt", "w", stdout);
    srand(time(NULL));
    int T = rand()%50 + 1;
    int R,C,K,r,c,n;
    printf("%d\n", T);
    while(T--)
    {
        R = rand()%200 + 1, C = rand()%200 + 1; K = rand()%112500+1;
        printf("%d %d %d\n", R,C,K);
        for (r=1; r<=R; ++r)
        {
            for (c=1; c<=C; ++c)
            {
                n = rand()%20 + 1;
                printf("%d ", n);
            }
            puts("");
        }
    }
    return 0;
}
