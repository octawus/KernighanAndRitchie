#include<ctype.h>
#include<stdio.h>

int getchar(void);
int ungetc (int , FILE *);
char *gets(char *buffer);
int get_float(float *);

void main(){
    
    float number = 0.0;
    int status = 0;
    char s[100];
    float *pn = &number;


    status = get_float(pn);

    printf("float: %f, status: %d, rest of line:", number, status);
    while(putchar(getchar()) != '\n');

}

/* getint: get next integer from input into *pn */

int get_float(float *pn){
    
    int c, sign, sign_symbol;
    float power;

    while (isspace(c = getchar()));

    if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
        ungetc(c, stdin);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1; //If c is '-' sign = -1 else sign = 1
    sign_symbol = c;
    if(c == '+' || c == '-')
        c = getchar();
    if(!isdigit(c) && c != '.')
        ungetc(sign_symbol, stdin);
    
    for (*pn = 0.0; isdigit(c); c = getchar())
        *pn = 10.0 * *pn + (c - '0');
    if(c == '.'){
        c = getchar();
    }
    
    for(power = 1.0; isdigit(c); c=getchar()){
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }

    *pn *= sign/power;

    if (c != EOF)
        ungetc(c, stdin);
    return c;
}