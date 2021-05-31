#include<ctype.h>
#include<stdio.h>

int getchar(void);
int ungetc (int , FILE *);
char *gets(char *buffer);
int get_int(int *);

void main(){
    
    int number = 0, status = 0;
    char s[100];
    int *pn = &number;


    status = get_int(pn);

    printf("integer: %d, status: %d, rest of line:", number, status);
    while(putchar(getchar()) != '\n');

}

/* getint: get next integer from input into *pn */

int get_int(int *pn){
    
    int c, sign, sign_symbol;

    while (isspace(c = getchar()));

    if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetc(c, stdin);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1; //If c is '-' sign = -1 else sign = 1
    sign_symbol = c;
    if(c == '+' || c == '-')
        c = getchar();
    if(!isdigit(c))
        ungetc(sign_symbol, stdin);
    for (*pn = 0; isdigit(c); c = getchar())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetc(c, stdin);
    return c;
}
