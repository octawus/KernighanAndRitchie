#include <stdio.h>

#define TRUE 1
#define FALSE 0

void main(){

    int c, found_letter = FALSE, new_line = TRUE;

    while(((c = getchar()) != EOF)){
        if(c != ' ' && c != '\t' && c != '\n'){
            found_letter = TRUE;
        }
        if(found_letter == TRUE){
            putchar(c);
        }
        if(found_letter == TRUE && (c == ' ' || c == '\t')){
            putchar('\n');
            found_letter = FALSE;
        }
    }
}