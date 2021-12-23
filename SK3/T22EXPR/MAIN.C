/* Kononov Svyatoslav, 09-3, 07.12.2018 */

#include <stdio.h>
#include <setjmp.h>
#include <stdarg.h>
#include <conio.h>
#include "expr.h"

jmp_buf ExprJumpBuf;

void GetStr( char *Str, int MaxLen )
{
  int i = 0;
  char ch;
   
  while ((ch = getchar()) != '\n')
    if (Str != NULL && i < MaxLen - 1)
      Str[i++] = ch;
  if (Str != NULL && i < MaxLen)
    Str[i] = 0;
}

void Error( char *Str, ... )
{
  va_list ap;

  printf("ERROR: ");
  va_start(ap, Str);
  vprintf(Str, ap);
  va_end(ap);
  printf("\n");
  longjmp(ExprJumpBuf, 1);
}

/* The main function */
void main( void )
{
  char str[MAX];
  QUEUE Q = {NULL, NULL};
  QUEUE QRes = {NULL, NULL};

  printf("Input an expression: ");
  GetStr(str, sizeof(str));
  Scanner(&Q, str);
  printf("Scanned queue: ");
  Parser(&QRes, &Q);
  DisplayQueue(&QRes);
  Eval(&QRes);
  _getch();
  ClearQueue(&Q);
} /* End of main function */

/* End of "MAIN.C" file */