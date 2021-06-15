#include <stdio.h>
#include <math.h>

int main()
{
    int intSize;
    float floatSize;
    double doubleSize;
    char charSize;

    short int sintSize;
    long int lintSize;

    printf("Size of int: %zu bytes\n", sizeof(intSize));
    printf("Size of float: %zu bytes\n", sizeof(floatSize));
    printf("Size of double: %zu bytes\n", sizeof(doubleSize));
    printf("Size of char: %zu bytes\n", sizeof(charSize));
    printf("Size of short int: %zu bytes\n", sizeof(sintSize));
    printf("Size of long int: %zu bytes\n", sizeof(lintSize));

    printf("Range of int is: %d to %d\n", (int)-(pow(2, ((sizeof(intSize) * 8) - 1))), (int)pow(2, ((sizeof(intSize) * 8) - 1)) - 1);
    printf("Range of float is: %f to %f\n", (float)-(pow(2, ((sizeof(floatSize) * 8) - 1))), (float)pow(2, ((sizeof(floatSize) * 8) - 1)) - 1);
    printf("Range of double is: %f to %f\n", (double)-(pow(2, ((sizeof(doubleSize) * 8) - 1))), (double)pow(2, ((sizeof(doubleSize) * 8) - 1)) - 1);
    printf("Range of char is: 0 to %d\n", (int)pow(2, ((sizeof(char) * 8) - 1)) - 1);
}





