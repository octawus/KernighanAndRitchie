#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 20

int main(){

    char c;
    int char_per_line = 0;
    
    while((c = getchar()) != EOF)
    {   
        if(char_per_line == MAX_CHAR_PER_LINE){
            putchar('\n');
            char_per_line = 0;
        }
        if(char_per_line == 0){
            c = toupper(c);
        }
        if(char_per_line > 0){
            c = tolower(c);
        }
        if(isprint(c) == 0 ){
            c = 
        }
        char_per_line++;
        putchar(c);
        if(c == '\n'){
            char_per_line = 0;
        }
    }

    return 0;
}

