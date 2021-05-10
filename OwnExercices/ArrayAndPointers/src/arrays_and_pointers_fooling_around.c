#include <stdio.h>
#include "string_processing.h"

int main(){

    int *integer_arr;

    integer_arr = generate_string(3,3,9);

    for( int i = 0; i < 9; i++){
        putchar(*(integer_arr + i));
    }

    return 0;
}

