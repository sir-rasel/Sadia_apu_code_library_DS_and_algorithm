#include<stdio.h>
#include<stdlib.h>
typedef struct nodes
{
    int i;
    struct nodes *prev;
    struct nodes *next;
} node;
node *start, *head;
int r;
void insert(node *p, int i)
{
    if (p->next->prev==NULL)
    {
        node *use;
        use = (node *) malloc(sizeof(node));
        use->i = i;
        use->prev = p;
        use->next = start;
        p->next = use;
    }
    else if (i>=p->next->i) insert(p->next,i);
    else
    {
        node *use;
        use = (node *) malloc(sizeof(node));
        use->i = i;
        use->prev = p;
        use->next = p->next;
        p->next->prev = use;
        p->next = use;
    }
}
void print(node *p)
{
    if (p==start) return;
    printf("%d ",p->i);
    if (p->next->prev == NULL) return;
    else print(p->next);
}
void clear(node *p)
{
    if (p->next == start) return;
    else clear(p->next);
    free(p);
}
void del(node *p,int i)
{
    if (r) return;
    if (p!=start && p->i==i)
    {
        p->prev->next = p->next;
        if (p->next != start) p->next->prev = p->prev;
        free(p);
        r=1;
        return;
    }
    if (p->next->prev == NULL)
    {
        r=-1;
        return;
    }
    else del(p->next,i);
}
int main()
{
    int i,d;
    start = (node *) malloc(sizeof(node));
    head = (node *) malloc(sizeof(node));
    head->prev = NULL;
    head->next = start;
    start->next = start;
    start->prev = NULL;
    while(scanf("%d%d",&d,&i)!=EOF)
    {
        r=0;
        if (d==1) insert(start,i);
        else if (d==2)
        {
            del(start,i);
            if (r==-1) printf("%d is not in the list\n",i);
        }
        printf("The list is : ");
        print(start->next);
        puts("");
    }
    printf("The final list is : ");
    print(start->next);
    clear(start);
    return 0;
}
