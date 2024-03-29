#include <stdio.h>

#define MAXLINE 1000 

void reverse(char s[]);
int mgetline(char line[], int lim);

void main(){
    int len;                /* current line length */
    char line[MAXLINE];     /* current input line */

    while((len = mgetline(line, MAXLINE)) > 0){
        reverse(line);
        printf("%s", line);
    }
}

void reverse(char rline[])
{
  int i,j;
  char temp;

  for(i=0;rline[i]!='\0';++i)
    ;

  --i;

  if(rline[i]=='\n') --i;

  j = 0;

  while(j < i)
  {
    temp = rline[j];
    rline[j] = rline[i];
    rline[i] = temp;
    --i;
    ++j;
  }
}

int mgetline(char s[],int lim)
{
  int i,c;
  
  for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if( c == '\n')
  {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}