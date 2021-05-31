#include<stdio.h>


#define NO_OF_LETTERS 26
/* count digits, white spaces, others*/

void main(){

    int c, i, nwhite, nother;
    int nletters[NO_OF_LETTERS];

    nwhite = nother = 0;
    for (i = 0; i < NO_OF_LETTERS; ++i){
        nletters[i] = 0;
    }

    while(((c = getchar()) != EOF)){
        if (c >= 'a' && c <= 'z')
            ++nletters[c-'a'];
    }
    printf("letters =");
    for(i = 0; i<NO_OF_LETTERS; i++)
        printf(" %d", nletters[i]);
    
}
