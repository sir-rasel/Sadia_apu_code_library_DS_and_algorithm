#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
class Trie
{
    int prefix, word;
    Trie *edges[26];
    void add(char *w, Trie &t)
    {
        ++t.prefix;
        if (!(*w))
        {
            ++t.word;
            return;
        }
        printf("%c\n",*w);
        int v = *w - 'a';
        if (t.edges[v] == NULL) t.edges[v] = new Trie;
        add(w+1, *t.edges[v]);
    }
    int countW(char *w, Trie &t)
    {
        if (!(*w)) return t.word;
        int v = *w - 'a';
        if (t.edges[v] == NULL) return 0;
        return countW(w+1, *t.edges[v]);
    }
    int countP(char *w, Trie &t)
    {
        if (!(*w)) return t.prefix;
        int v = *w - 'a';
        if (t.edges[v] == NULL) return 0;
        return countP(w+1, *t.edges[v]);
    }
    void clearA(Trie *t)
    {
        if (t==NULL) return;
        int i;
        for (i=0; i<26; ++i)
        {
            clearA((*t).edges[i]);
            delete (*t).edges[i];
        }
    }
public:
    Trie()
    {
        prefix = word = 0;
        for (int i=0; i<26; ++i) edges[i] = NULL;
    }
    void addWord(char *w)
    {
        add(w, *this);
    }
    int countWord(char *w)
    {
        return countW(w, *this);
    }
    int countPrefix(char *w)
    {
        return countP(w, *this);
    }
    void clear()
    {
        clearA(this);
    }
};
char word[100];
int main()
{
    Trie tt;
    while(scanf("%s",word)!=EOF) tt.addWord(word);
    while(scanf("%s",word)!=EOF)
    {
        printf("%d %d\n",tt.countWord(word), tt.countPrefix(word));
    }
    tt.clear();
    return 0;
}
