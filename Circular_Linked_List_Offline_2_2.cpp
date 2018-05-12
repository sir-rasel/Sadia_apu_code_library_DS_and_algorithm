#include<stdio.h>
#include<stdlib.h>
typedef struct nodes
{
    int i;
    struct nodes *prev;
    struct nodes *next;
} node;
node *head;
void print(node *p)
{
    if (p->next == head->next) return;
    printf("%d ",p->i);
    print(p->next);
}
void insert(node *p, int i)
{
    if (p->next==head->next)
    {
        p->i = i;
        node *use = (node *) malloc(sizeof(node));
        p->next = use;
        use->next = head->next;
        use->prev = p;
        head->next->prev = use;
    }
    else if (i>p->i) insert(p->next,i);
    else
    {
        node *use = (node *) malloc(sizeof(node));
        use->prev = p->prev;
        p->prev->next = use;
        use->next = p;
        p->prev = use;
        use->i = i;
        if (p==head->next) head->next = use;
    }
}
void clear(node *p)
{
    if (p->next != head->next) clear(p->next);
    free(p);
}
int del(node *p,int i)
{
    if (p->next==head->next) return -1;
    if (p->i == i)
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (p==head->next) head->next = p->next;
        free(p);
        return 1;
    }
    else return del(p->next,i);
}
int main()
{
    int i,d;
    head = (node *) malloc(sizeof(node));
    node *start = (node *) malloc(sizeof(node));
    head->next = start;
    start->prev = start;
    start->next = start;
    while(scanf("%d%d",&d,&i)!=EOF)
    {
        if (d==1) insert(head->next,i);
        else if (d==2)
        {
            if (del(head->next,i)==-1) printf("%d Not Found\n",i);
        }
        printf("The List is : ");
        print(head->next);
        puts("");
    }
    printf("The Final List is : ");
    print(head->next);
    puts("");
    free(head->next);
    free(start);
    free(head);
    return 0;
}
