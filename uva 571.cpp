#include<stdio.h>
#define MAX 1003
enum {none, fA, fB, eA, eB, A2B, B2A};
int A,B,N,f;
struct position
{
    int mark,parent,A,B,step;
} pos[MAX*MAX];
int jugcond[MAX][MAX];
void setjug(int end, int mark, int parent, int A, int B, int step)
{
    pos[end].step = step;
    pos[end].mark = mark;
    pos[end].parent = parent;
    pos[end].A = A;
    pos[end].B = B;
    pos[end].step = step;
}
void printc(int node)
{
    switch(pos[node].mark)
    {
        case fA: puts("fill A"); break;
        case fB: puts("fill B"); break;
        case eA: puts("empty A"); break;
        case eB: puts("empty B"); break;
        case A2B: puts("pour A B"); break;
        case B2A: puts("pour B A"); break;
    }
}
void printpath(int node)
{
    if (node==0) return;
    printpath(pos[node].parent);
    printc(node);
}
int check(int end)
{
    if (pos[end].A==N || pos[end].B==N)
    {
        f=1;
        printpath(end);
        return 1;
    }
    else return 0;
}
int main()
{
    int i,j,k;
    int start,end;
    while(scanf("%d%d%d",&A,&B,&N)!=EOF)
    {
        f=0;
        for (i=0; i<=A; i++)
        {
            for (j=0; j<=B; j++) jugcond[i][j]=0;
        }
        start = 1;
        end = 1;
        jugcond[0][0] = 1;
        setjug(end,none,none,0,0,0);
        end++;
        while(start<end)
        {
            if (jugcond[A][pos[start].B]==0)
            {
                setjug(end+1,fA,start,A,pos[start].B,pos[start].step+1);
                jugcond[A][pos[start].B] = 1;
                if (check(end)) break;
                end++;
            }
            if (jugcond[pos[start].A][B]==0)
            {
                setjug(end+1,fB,start,pos[start].A,B,pos[start].step+1);
                jugcond[pos[start].A][B] = 1;
                if (check(end)) break;
                end++;
            }
            if (jugcond[0][pos[start].B]==0)
            {
                setjug(end+1,eA,start,0,pos[start].B,pos[start].step+1);
                jugcond[0][pos[start].B] = 1;
                if (check(end)) break;
                end++;
            }
            if (jugcond[pos[start].A][0]==0)
            {
                setjug(end+1,eB,start,pos[start].A,0,pos[start].step+1);
                jugcond[pos[start].A][0] = 1;
                if (check(end)) break;
                end++;
            }
            if (pos[start].A>0 && pos[start].B<B)
            {
                int x = B - pos[start].B;
                if (pos[start].A>x)
                {
                    if (jugcond[pos[start].A-x][B]==0)
                    {
                        setjug(end+1,A2B,start,pos[start].A-x,B,pos[start].step+1);
                        jugcond[pos[start].A-x][B] = 1;
                        if (check(end)) break;
                        end++;
                    }
                }
                else
                {
                    if (jugcond[0][pos[start].B+pos[start].A]==0)
                    {
                        setjug(end+1,A2B,start,0,pos[start].B+pos[start].A,pos[start].step+1);
                        jugcond[0][pos[start].B+pos[start].A] = 1;
                        if (check(end)) break;
                        end++;
                    }
                }
            }
            if (pos[start].B>0 && pos[start].A<A)
            {
                int x = A - pos[start].A;
                if (pos[start].B>x)
                {
                    if (jugcond[A][pos[start].B-x]==0)
                    {
                        setjug(end+1,B2A,start,A,pos[start].B-x,pos[start].step+1);
                        jugcond[A][pos[start].B-x] = 1;
                        if (check(end)) break;
                        end++;
                    }
                }
                else
                {
                    if (jugcond[pos[start].B+pos[start].A][0]==0)
                    {
                        setjug(end+1,B2A,start,pos[start].B+pos[start].A,0,pos[start].step+1);
                        jugcond[pos[start].B+pos[start].A][0] = 1;
                        if (check(end)) break;
                        end++;
                    }
                }
            }
            start++;
        }
        if (f) puts("success");
        else puts("failure");
    }
    return 0;
}
