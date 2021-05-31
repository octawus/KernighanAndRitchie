#include<stdio.h>
#include<string.h>
#define MAXSIZE 100

int strend(char *, char *);

void main()
{
    char string1[MAXSIZE], string2[MAXSIZE];

    printf("Introduce un primer string:\n");
    scanf("%s", string1);
    printf("Introduce un segundo string:\n");
    scanf("%s", string2);

    printf("%d", strend(string1, string2));
}

int strend(char *s, char *t)
{
    if (!s || !t)
        return 0;
    size_t lenstr = strlen(s);
    size_t lensuffix = strlen(t);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(s + lenstr - lensuffix, t, lensuffix) == 0;
}