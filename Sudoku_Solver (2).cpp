#include<stdio.h>
#include<string.h>
using namespace std;
char grid[10][10];
int board[9][9];
int rowmask[9];
int colmask[9];
int zonemask[9];
bool done;
int calc_zone(int i, int j)
{
    i /= 3;
    j /= 3;
    if (i==0) return j;
    if (i==1) return 3+j;
    return 6+j;
}
void binary(int x)
{
    if (!x) return;
    printf("%d",x%2);
    binary(x/2);
}
void bktk(int x, int y)
{
    if (done) return;
    int i,z=calc_zone(x,y),j,k;
    int nextx=-1, nexty=-1;
    for (k=y+1; k<9; ++k)
    {
        if (!board[x][k])
        {
            nextx = x;
            nexty = k;
            break;
        }
    }
    if (nextx==-1)
    {
        bool found = false;
        for (j=x+1; j<9; ++j)
        {
            for (k=0; k<9; ++k)
            {
                if (!board[j][k])
                {
                    nextx = j, nexty = k;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    for (i=1; !done && i<=9; ++i)
    {
        if ((rowmask[x]&(1<<i))==0 && (colmask[y]&(1<<i))==0 && (zonemask[z]&(1<<i))==0)
        {
            rowmask[x] |= (1<<i);
            colmask[y] |= (1<<i);
            zonemask[z] |= (1<<i);
            board[x][y] = i;
            if (nextx>-1) bktk(nextx, nexty);
            else
            {
                bool isvalid = true;
                for (j=0; j<9; ++j)
                {
                    if (rowmask[j]!=1022) isvalid = false;
                }
                if (isvalid)
                {
                    for (j=0; j<9; ++j)
                    {
                        for (k=0; k<9; ++k) printf("%d",board[j][k]);
                        puts("");
                    }
                    done = true;
                    break;
                }
            }
            rowmask[x] &=~ (1<<i);
            colmask[y] &=~ (1<<i);
            zonemask[z] &=~ (1<<i);
            board[x][y] = 0;
        }
    }
}
int main()
{
    freopen("data.txt","r",stdin);
    int T,t;
    int i,j,x;
    scanf("%d",&T);
    for (t=1; t<=T; ++t)
    {
        memset(rowmask, 0, sizeof(rowmask));
        memset(colmask, 0, sizeof(colmask));
        memset(zonemask, 0, sizeof(zonemask));
        printf("Case %d:\n",t);
        done = false;
        for (i=0; i<9; ++i)
        {
            scanf("%s",grid[i]);
            for (j=0; j<9; ++j)
            {
                if (grid[i][j]!='.')
                {
                    x = grid[i][j] - '0';
                    board[i][j] = x;
                    rowmask[i] |= (1<<x);
                    colmask[j] |= (1<<x);
                    zonemask[calc_zone(i,j)] |= (1<<x);
                }
                else board[i][j] = 0;
            }
        }
        bool f = false;
        for (i=0; i<9; ++i)
        {
            for (j=0; j<9; ++j)
            {
                if (!board[i][j])
                {
                    bktk(i,j);
                    f = true;
                    break;
                }
            }
            if (f) break;
        }
    }
    return 0;
}
