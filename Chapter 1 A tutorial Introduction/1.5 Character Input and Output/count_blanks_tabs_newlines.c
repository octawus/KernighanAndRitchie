#include <stdio.h>

void main(){

    int c, total_count;


    while((c = getchar()) != EOF){
        if (c == ' ' || c == '\t' || c == '\n')
            ++total_count;
    }

    printf("%d\n", total_count);

}