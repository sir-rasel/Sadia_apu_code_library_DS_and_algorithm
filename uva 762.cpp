#include<stdio.h>
#include<string.h>
#define MAX 680
char temp[3];
char cities[MAX][3],check[MAX];  /* cities[] holds the names , check[] holds the record whether a node has been used or not */
int ct[MAX][MAX],t[MAX];  /* ct[][] holds records of the children of any node */
int orig,des;
int c;
int queue[MAX],start,end,source[MAX];  /* source[] holds data that from which parent the child is created */
char res1[MAX], res2[MAX];
int r;
char ch;
int find_indx()
{
    int i;
    for (i=1; i<c; i++)
    {
        if (strcmp(temp,cities[i])==0) return i;
    }
    strcpy(cities[c++],temp);
    return i;
}
int main()
{    
    int n,f,F=0,C;
    int i,j,p;
    while(scanf("%d",&n)!=EOF)
    {
        if (F==0) F++;
        else printf("\n");
        ch= getchar();
        for (i=1; i<MAX; i++) 
        {
            check[i]=source[i]=0;
            t[i]=1;
        }
        f=0;
        c=r=1;
        for (i=0; i<n; i++)
        {
            scanf("%s",temp);
            j= find_indx();
            scanf("%s",temp);
            p=find_indx();
            ct[j][t[j]++]=p; 
            ct[p][t[p]++]=j;
        }
        C=c;
        /*
        for (i=1; i<c; i++)
        {
            printf("%s : ",cities[i]);
            for (j=1; j<t[i]; j++) printf("%s ",cities[ct[i][j]]);
            printf("\n");
        } 
        */    
        scanf("%s",temp);
        orig= find_indx();
        scanf("%s",temp);
        des= find_indx();
        start=end=1;
        queue[end++]=orig;
        if (orig>=C || des>=C) 
        {
            printf("No route\n");
            continue;
        }
        
        while(start<end)
        {
            if (queue[start]==des)
            {
                f=1;
                break;
            }
            for (i=1; i<t[queue[start]]; i++)
            {
                if (check[ct[queue[start]][i]]==0)
                {
                    check[ct[queue[start]][i]]=1;
                    source[end]=start;
                    queue[end++]= ct[queue[start]][i];
                }
            }
            start++;
        }
        if (f)
        {
            j=start;
            r=1;
            while(queue[j]!=orig)
            {
                res1[r]= queue[source[j]];
                res2[r++]=queue[j];
                j= source[j];
            }
            for (i=r-1; i; i--) printf("%s %s\n",cities[res1[i]],cities[res2[i]]);
        }
        else printf("No route\n");
        ch= getchar();
    }
    return 0;
}
