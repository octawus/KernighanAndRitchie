#include<ctype.h>
#include<stdio.h>

int getchar(void);
int ungetc (int , FILE *);
int get_int(int *);

void main(){
    
    int number = 0, status = 0;
    int *pn = &number;


    status = get_int(pn);

    printf("integer: %d, status: %d \n", number, status);

}

/* getint: get next integer from input into *pn */

int get_int(int *pn){
    
    int c, sign;

    while (isspace(c = getchar()));

    if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetc(c, stdin);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1; //If c is '-' sign = -1 else sign = 1
    if(c == '+' || c == '-')
        c = getchar();
    for (*pn = 0; isdigit(c); c = getchar())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetc(c, stdin);
    return c;
}