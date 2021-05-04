#include <stdio.h>

/*print Fahrenheit-Celsius table
    for fahr = 0, 20, ... , 300; floating-point version*/

void main(){

    float fahr, celsius;
    int lower, upper, step;

    lower = 0; /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20; /* step size */

    fahr = lower;

    printf("%10s\t%10s\n", "Fahrenheit", "Celsius");

    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%10.0f\t%10.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

}

/*%3.0f says that a floating-point number is 
to be printed at leas three characters wide,
with no decimal point an no fraction digits.*/

/*%6.1f describes another number that is to be 
printed at least six characters wide, with 1 digit
after the decimal point.*/

/* among others, printf also recognizes %o for octal,
%x for hexadecimal, %c for characters, %s for characters 
string, and %% for % itself*/