#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 20

int main(){

    char c;
    int char_per_line = 0;
    
    while((c = getchar()) != EOF)
    {   
        if(iscntrl(c) || c == ' ')
        {
            /* non-graphic or blank character */
            printf("\\%03o",c);
            if(c == '\n'){
                char_per_line = 0;
                putchar('\n');
            }
        }
        else{
            if(char_per_line == MAX_CHAR_PER_LINE){
                printf("\\%03o",'\n');
                putchar('\n');
                char_per_line = 0;
            }
            if(char_per_line == 0){
                c = toupper(c);
            }
            if(char_per_line > 0){
                c = tolower(c);
            }
            char_per_line++;
            putchar(c);
        }
    }

    return 0;
}

