#include <stdio.h>
#include "../Utils/string_procesing.h"

#define MAXLINE 1000 

void reverse(char s[]);
int get_line(char s[], int len);

void main(){
    int len;                /* current line length */
    char line[MAXLINE];     /* current input line */

    while((len = get_line(line, MAXLINE)) > 0){
        reverse(line);
        printf("%s", line);
    }
}