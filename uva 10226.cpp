#include<stdio.h>
#include<iostream>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
int main()
{
    int f=0;
    /*freopen("data.txt","r",stdin);*/
    map<string, long> data;
    map<string, long> :: iterator it;
    char input[36];
    long n,tot;
    scanf("%ld",&n);
    input[0]=getchar();
    gets(input);
    while(n--)
    {
        if (!f) f++;
        else printf("\n");
        tot=0;
        while(gets(input)!=NULL)
        {
            if (!strlen(input)) break;
            data[input]++;
            tot++;
        }
        for (it = data.begin(); it!=data.end(); it++)
        {
            string s = it->first;
            long x = it->second;
            printf("%s %.4lf\n",s.c_str(),(double) 100*x/tot);
        }
        data.clear();
    }
    return 0;
}
