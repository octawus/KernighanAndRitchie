#include <stdio.h>
#include "string_procesing.h"

int * generate_string(int, int, int);

void main(){

    int *integer_arr = generate_string(3, 3, 9);

    for( int i = 0; i < 9; i++){
        putchar(*(integer_arr + i));
    }
}

