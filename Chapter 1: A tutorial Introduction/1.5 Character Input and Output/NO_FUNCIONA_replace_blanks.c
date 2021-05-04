#include<stdio.h>

#define TRUE 1
#define FALSE 0

/*NO FUNCIONA, PREGUNTAR DUDAS*/

void main(){
    
    int c, number_of_blanks = 0, found_letter = FALSE;

    while((c = getchar()) != EOF){
        if(c != ' ' && c != '\n' && found_letter == FALSE){
            found_letter = TRUE;
            for(int i = 0; i < number_of_blanks; i++)
                putchar(' ');
            putchar(c);
        }else if(c == ' ' && found_letter == FALSE){
           ++number_of_blanks;
        }else if (found_letter != TRUE && c == '\n'){
            putchar(' ');
            putchar('\n');
        }else if (found_letter == TRUE){
            putchar(c);
        }

    }
}