#include<stdio.h>
char str[103];
char text[1003];
int failure[103];
int main()
{
    int i,j,f,count;
    scanf("%s",str);
    f = -1;
    failure[0] = -1;
    for (i=1; str[i]; ++i)
    {
        while(f!=-1 && str[f+1]!=str[i]) f = failure[f];
        if (str[f+1]==str[i]) ++f;
        failure[i] = f;
    }
//     smallest unit of the string
    f = i - f - 1;
    for (i=0; i<f; ++i) printf("%c",str[i]);
    puts("");

    // match with another string, str[] is the pattern
    scanf("%s",text);
    f = -1;
    count = 0;
    for (i=0; text[i]; ++i)
    {
        while (f!=-1 && text[i]!=str[f+1]) f = failure[f];
        if (text[i]==str[f+1]) ++f;
        if (!str[f+1])
        {
            ++count;
            f = failure[f];
        }
    }
    printf("%d\n",count);
    return 0;
}
