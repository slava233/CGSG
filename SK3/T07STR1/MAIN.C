#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char * Load( char *FileName )
{
  FILE *F;
  char *mem = NULL;

  if((F = fopen("D:\\SK3A\\ORWELL.TXT", "r")) != NULL)
  {
    int flen = 0;

    while (fgetc(F) != EOF)
      flen++;

    if((mem =  malloc(flen + 1)) != NULL) 
    {
      rewind(F);
      fread(mem, 1, flen, F);
      mem[flen] = 0;
    }
    fclose(F);
  }
  return mem;
}
int WordCount(char *Str)
{
  int i = 0, cnt = 0;
  char old = ' ';

  while (Str[i] != 0)
  {
    cnt += isspace((unsigned char)old) && !isspace((unsigned char)Str[i]);
    old = Str[i++];
  }
  return cnt;
}
                                                              
void LetCount( char *Str )
{
  int l[26], i, k;

  for (i = 0; i < 26; i++)
    l[i] = 0;

  for (i = 0; Str[i] != 0; i++)
    for (k = 65; k <= 90; k++)
      if (((int)Str[i] == k) || ((int)Str[i] == k + 32))
        l[k - 65]++; 

  for (i = 0, k = 65; i < 26; i++, k++)
    printf("Number of %c letter is %i\n", k, l[i]);
}

int StrCount( char *Str )
{
  int i = 0, cnt = 0;

  while (Str[i] != 0)
    cnt += Str[i++] == '\n';
  return cnt;
}


void main( void )
{
  char *txt = Load("D:\\SK3A\\ORWELL.TXT");
  if (txt == NULL)
    return;
  printf("Number of lines is %d\n", StrCount(txt));
  printf("Number of words is %d\n", WordCount(txt));
  LetCount(txt);
  free(txt);                                                                                 
  _getch();  
}

                                                                                                                                                    