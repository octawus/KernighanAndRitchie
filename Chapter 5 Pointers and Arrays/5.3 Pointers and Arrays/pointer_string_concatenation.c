#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXSIZE 1000


void str_cat (char *, char *);

void main()
{   
    char string1[MAXSIZE], string2[MAXSIZE];

    printf("Introduce un primer string:\n");
    scanf("%s", string1);
    printf("Introduce un segundo string:\n");
    scanf("%s", string2);

    str_cat(string1, string2);

    printf("%s", string1);
}

void str_cat (char *s, char *t)
{
    while(*s){
        s++;
    }
    while(*t){
        *s = *t;
        s++;
        t++;
    }
    *s = '\0';
}

