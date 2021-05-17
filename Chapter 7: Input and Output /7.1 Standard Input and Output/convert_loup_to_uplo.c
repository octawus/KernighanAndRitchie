#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (int argc, char **argv)
{   
    char c;

    if (strcmp(argv[1], "toupper") == 0){
        while ((c = getchar()) != EOF)
        {
            putchar(toupper(c));
        }    
    }else if(strcmp(argv[1], "tolower") == 0)
    {
        while((c = getchar()) != EOF)
        {
            putchar(tolower(c));
        }
    }else{
        printf("[ERROR] invalid argument\n");
    }

    return 0;
}