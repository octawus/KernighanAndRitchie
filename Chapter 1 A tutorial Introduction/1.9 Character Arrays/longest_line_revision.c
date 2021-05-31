#include<stdio.h>
#define MAXLINE 100 /*maximum input line size*/

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/*print longest input line*/

void main(){
    int len;                /* current line length */
    int max = 0;                /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while((len = get_line(line, MAXLINE)) > 0)
        if(len > max) {
            max = len;
            copy(longest, line);
        }
        
    if (max > 0)            /*there was a line */
        printf("The longest string was: %s, with a lenght of: %d", longest, max);

}

/* getline: read a line into s, return length */
int get_line(char s[], int lim){
    int c, i;

    i = 0;

    while(((c = getchar()) != EOF) && c != '\n'){
        if( i < lim - 1)
            s[i] = c;
        ++i;
    }

    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;

}

void copy(char to[], char from[]){
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;

}