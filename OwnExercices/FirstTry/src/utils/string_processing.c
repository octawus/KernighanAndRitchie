#include <stdio.h>
#include <string.h>
#include "string_processing.h"

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

/* returns lenght of string s */
int string_lenght(char *s)
{
    int n ;

    for(n = 0; *s != '\0'; s++){
        n++;
    }

    return n;
}

/* generates a string by jumping values */
int *generate_string(int start_position, int jumping_value, int size_of_string){

    int s[size_of_string];

    *s = start_position;

    for( int i = 1; i < size_of_string; i++){
        *(s+i) = *(s+i-1) + jumping_value;
    }

    return s;
}