// Trie
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
#define MAXSIZE 100000
int Trie[MAXSIZE+6][27],node;
bool vis[MAXSIZE+6];
void initialize() {memset(Trie, -1, sizeof(Trie)); node=0; memset(vis, false, sizeof(vis));}
void insert(char *str)
{
    int cur = 0,idx;
    char *ch = str;
    while(*ch)
    {
        idx = *ch - 'a' + 1;
        if (Trie[cur][idx]==-1) Trie[cur][idx]= ++node;
        cur = Trie[cur][idx];
        ++ch;
    }
    vis[cur] = true;
}
bool check(char *str)
{
    int cur = 0,idx;
    char *ch = str;
    while(*ch)
    {
        idx = *ch - 'a' + 1;
        if (Trie[cur][idx]==-1) return false;
        cur = Trie[cur][idx];
        ++ch;
    }
    if (vis[cur]) return true;
    return false;
}
int main()
{
    int op;
    char str[16];
    initialize();
    while(scanf("%d %s", &op, str) != EOF)
    {
        if (op==1) insert(str);
        else printf("%d\n", check(str));
    }
    return 0;
}
