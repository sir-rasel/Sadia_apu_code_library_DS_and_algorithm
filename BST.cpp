#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct trees
{
    char word[20];
    int count;
    trees *left, *right;
};
trees *tree = (trees *) malloc(sizeof(trees));
void insert(char *word, trees *use)
{
    if (strcmp(word,use->word)==0)
    {
        use->count++;
        printf("found %d\n",use->count);
    }
    else if (strcmp(word,use->word)<0)
    {
        if (use->left==NULL)
        {
            trees *now = (trees *) malloc(sizeof(trees));
            strcpy(now->word,word);
            now->left = NULL;
            now->right = NULL;
            use->left = now;
            now->count = 1;
            printf("inserted %d\n",now->count);
        }
        else insert(word,use->left);
    }
    else if (strcmp(word,use->word)>0)
    {
        if (use->right==NULL)
        {
            trees *now;
            now = (trees *) malloc(sizeof(trees));
            strcpy(now->word,word);
            now->left = NULL;
            now->right = NULL;
            use->right = now;
            now->count = 1;
            printf("inserted %d\n",now->count);
        }
        else insert(word,use->right);
    }
}
void print(trees *use)
{
    if (use!=NULL)
    {
        print(use->left);
        printf("%s %d\n",use->word,use->count);
        print(use->right);
    }
}
void clear(trees *use)
{
    if (use->left!=NULL) clear(use->left);
    if (use->right!=NULL) clear(use->right);
    free(use);
}
int main()
{
    int f;
    char word[20];
    tree->word[0] = 0;
    tree->left = NULL;
    tree->right = NULL;
    while(scanf("%s",word)!=EOF) insert(word,tree);
    print(tree->right);
    clear(tree);
    return 0;
}
