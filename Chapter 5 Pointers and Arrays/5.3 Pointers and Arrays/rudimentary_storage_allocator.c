#include<stdio.h>

#define ALLOCSIZE 100 /* size of available space */

static char allocbuf[ALLOCSIZE]; /*storage for alloc*/
static char *allocp = allocbuf; /*next free position*/

char * alloc(int);
void afree(char *);

void main(){

    char * ptr = allocbuf;

    char * name = alloc(10);
    char * surname = alloc(10);

    name = "Mihai";
    surname = "Stanescu";

    printf("%s %s\n", name, surname);
    afree(surname);
    printf("%s %s\n", name, surname);
}

char * alloc(int n) /*return pointer to n characters*/
{
    if(allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n; /*old p*/
    }else /*not enough room*/
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}