#include<stdio.h>

#define TRUE 1
#define FALSE 0 

void main(){

    int c;

    while(((c = getchar()) != EOF )){
        if(c == '\t') {
            putchar('\\');
            putchar('t');
        }
        else if (c == '\b') {
            putchar('\\');
            putchar('b');
        }
        else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        else putchar(c);
    }
}