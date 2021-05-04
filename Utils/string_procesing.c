#include <stdio.h>
#include <string.h>

/*reverses s*/
void reverse(char s[])
{
    char *p1 = s;
    char *p2 = s + strlen(s) - 2;

    while (p1 < p2) {
        char tmp = *p1;
        *p1++ = *p2;
        *p2-- = tmp;
    }
}

/*reads a line into s, returns lenght*/
int get_line(char s[], int lim){
    int c, i;

    for(i=0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++){
        s[i] = c;
    }
    
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}