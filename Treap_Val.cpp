#include<stdio.h>
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
#include<iostream>
#include<assert.h>
#include<time.h>
using namespace std;
#define INF ((1LL<<31)-1)
struct T
{
    int key, priority, sz;
    T *left, *right;
    T() {}
    T(int key, int priority, T* left, T* right, int _sz = 1)
    {
        this->key = key;
        this->priority = priority;
        this->left = left, this->right = right;
        this->sz = _sz;
    }
    void update() {if (sz) sz = left->sz + 1 + right->sz;}
} *R, *nil; // nil indica un nod 'gol'
void init(T* &R)
{
    srand(unsigned(time(0)));
    R = nil = new T(0, 0, NULL, NULL, 0);
}
int search(T* n, int key)
{
    if (n == nil) return 0;
    if (key == n->key) return 1;
    if (key < n->key) return search(n->left, key);
    else return search(n->right, key);
}
void rotleft(T* &n)
{
    T *t = n->left;
    n->left = t->right, t->right = n;
    n->update(); t->update();
    n = t;
}
void rotright(T* &n)
{
    T *t = n->right;
    n->right = t->left, t->left = n;
    n->update(); t->update();
    n = t;
}
void balance(T* &n)
{
    if (n->left->priority > n->priority) rotleft(n);
    else if (n->right->priority > n->priority) rotright(n);
    n->update();
}
void insert(T* &n, int key, int priority)
{
    if (n == nil)
    {
        n = new T(key, priority, nil, nil);
        return;
    }
    if (key <= n->key) insert(n->left, key, priority);
    else if (key > n->key) insert(n->right, key, priority);
    balance(n);
}
void erase(T* &n, int key)
{
    if (n == nil) return;
    if (key < n->key) erase(n->left, key);
    else if (key > n->key) erase(n->right, key);
    else
    {
        if (n->left == nil && n->right == nil) delete n, n = nil;
        else
        {
            (n->left->priority > n->right->priority) ? rotleft(n) : rotright(n);
            erase(n, key);
        }
    }
    n->update();
}
void split(T* &R, T* &Ts, T* &Tg, int key)
{
    insert(R, key, INF);
    Ts = R->left, Tg = R->right;
    delete R, R = nil;
}
void join(T* &R, T* Ts, T* Tg, int key)
{
    R = new T(key, 0, Ts, Tg);
    erase(R, R->key);
}
int main()
{
    T *tree;
    init(tree);
    insert(tree, 5, rand()-1); printf("%d\n", tree->sz);
    insert(tree, 4, rand()-1); printf("%d\n", tree->sz);
    insert(tree, 3, rand()-1); printf("%d\n", tree->sz);
    insert(tree, 2, rand()-1); printf("%d\n", tree->sz);
    insert(tree, 1, rand()-1); printf("%d\n", tree->sz);
    erase(tree, 5); printf("%d\n", tree->sz);
    erase(tree, 1); printf("%d\n", tree->sz);
    erase(tree, 3); printf("%d\n", tree->sz);
    return 0;
}
