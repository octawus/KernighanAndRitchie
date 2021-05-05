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

    //printf("%s", (char)((char *)(&string1 + 1))[-1]);

    //printf("%ld", sizeof(string1));
    //printf("%ld", strlen(string1));

    printf("%d", strend(string1, string2));
    //putchar((((char *)(&string1 + 1))[-1]));

    //printf("%p\n", &string1);
    //printf("%p", &string1 + 1);

    //int *p = ((int *)(&string1 + 1))[-1];
    //printf("*p = %d\n", *p);
}


int strend(char *s, char *t)
{
    char * last_s = s + strlen(s);
    char * last_t = t + strlen(t);

    while((last_s-- == last_t--))
        ;
    if(last_t != t)
        return 0;
    else
        return 1;
}