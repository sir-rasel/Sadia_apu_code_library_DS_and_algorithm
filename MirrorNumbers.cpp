#include<stdio.h>
#include<string.h>
#define MAXLEN 19
bool vis[MAXLEN+3][MAXLEN+3][2][2][2];
int dp[MAXLEN+3][MAXLEN+3][2][2][2];
char str[MAXLEN+3];
int rec(int left, int right, int nz, int eq1, int eq2)
{
    if (left>right) return nz && (!eq1 || (eq1 && eq2));
    if (left==right)
    {
        if (nz && !eq1) return 3;
        if (!nz && eq1)
        {
            if (str[left]>='8') return 2;
            if (str[left]>='1') return 1;
            return 0;
        }
        if (!nz && !eq1) return 2;
        if (eq1 && !eq2)
        {
            if (str[left]>'8') return 3;
            if (str[left]>'1') return 2;
            if (str[left]>'0') return 1;
            return 0;
        }
        else if (eq1 && eq2)
        {
            if (str[left]>='8') return 3;
            if (str[left]>='1') return 2;
            return 1;
        }
    }
    if (vis[left][right][nz][eq1][eq2]) return dp[left][right][nz][eq1][eq2];
    vis[left][right][nz][eq1][eq2] = true;
    int ret = 0;
    if (!nz)
    {
        ret += rec(left+1, right, 0, 0, 0);
        if (eq1)
        {
            if (str[left]>'8') ret += rec(left+1, right-1, 1, 0, 0);
            else if (str[left]=='8')
            {
                if (str[right]>='8') ret += rec(left+1, right-1, 1, 1, 1);
                else ret += rec(left+1, right-1, 1, 1, 0);
            }
            if (str[left]>'1') ret += rec(left+1, right-1, 1, 0, 0);
            else if (str[left]=='1')
            {
                if (str[right]>='1') ret += rec(left+1, right-1, 1, 1, 1);
                else ret += rec(left+1, right-1, 1, 1, 0);
            }
            if (str[left]>'2') ret += rec(left+1, right-1, 1, 0, 0);
            else if (str[left]=='2')
            {
                if (str[right]>='5') ret += rec(left+1, right-1, 1, 1, 1);
                else ret += rec(left+1, right-1, 1, 1, 0);
            }
            if (str[left]>'5') ret += rec(left+1, right-1, 1, 0, 0);
            else if (str[left]=='5')
            {
                if (str[right]>='2') ret += rec(left+1, right-1, 1, 1, 1);
                else ret += rec(left+1, right-1, 1, 1, 0);
            }
        }
        else ret += 4*rec(left+1, right-1, 1, 0, 0);
    }
    else if (eq1)
    {
        if (str[left]>'8') ret += rec(left+1, right-1, 1, 0, 0);
        else if (str[left]=='8')
        {
            if (str[right]>='8') ret += rec(left+1, right-1, 1, 1, eq2);
            else ret += rec(left+1, right-1, 1, 1, 0);
        }
        if (str[left]>'1') ret += rec(left+1, right-1, 1, 0, 0);
        else if (str[left]=='1')
        {
            if (str[right]>='1') ret += rec(left+1, right-1, 1, 1, eq2);
            else ret += rec(left+1, right-1, 1, 1, 0);
        }
        if (str[left]>'0') ret += rec(left+1, right-1, 1, 0, 0);
        else if (str[left]=='0')
        {
            if (str[right]>='0') ret += rec(left+1, right-1, 1, 1, eq2);
            else ret += rec(left+1, right-1, 1, 1, 0);
        }
        if (str[left]>'2') ret += rec(left+1, right-1, 1, 0, 0);
        else if (str[left]=='2')
        {
            if (str[right]>='5') ret += rec(left+1, right-1, 1, 1, eq2);
            else ret += rec(left+1, right-1, 1, 1, 0);
        }
        if (str[left]>'5') ret += rec(left+1, right-1, 1, 0, 0);
        else if (str[left]=='5')
        {
            if (str[right]>='2') ret += rec(left+1, right-1, 1, 1, eq2);
            else ret += rec(left+1, right-1, 1, 1, 0);
        }
    }
    else ret += 5*rec(left+1, right-1, 1, 0, 0);
    return dp[left][right][nz][eq1][eq2] = ret;
}
int main()
{
    while(scanf("%s", str) != EOF)
    {
        memset(vis, false, sizeof(vis));
        printf("%d\n", 1+rec(0, strlen(str)-1, 0, 1, 1));
    }
    return 0;
}
