/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include <stdio.h>
#include <setjmp.h>
#include <stdarg.h>
#include <conio.h>
#include "expr.h"

jmp_buf ExprJumpBuf;

/* Start of 'GetStr' function */
void GetStr( char *Str, int MaxLen )
{
  int i = 0;
  char ch;
   
  while ((ch = getchar()) != '\n')
    if (Str != NULL && i < MaxLen - 1)
      Str[i++] = ch;
  if (Str != NULL && i < MaxLen)
    Str[i] = 0;
} /* End of 'GetStr' function */

/* Start of 'Error' function */
void Error( char *Str, ... )
{
  va_list ap;

  printf("ERROR: ");
  va_start(ap, Str);
  vprintf(Str, ap);
  va_end(ap);
  printf("\n");
  longjmp(ExprJumpBuf, 1);
} /* End of 'Error' function */

/* Start of 'Main' function */
void main( void )
{
  char str[MAX];
  QUEUE Q = {NULL, NULL};
  QUEUE QRes = {NULL, NULL};

  if (setjmp(ExprJumpBuf))
  {
    ClearQueue(&Q);
    ClearQueue(&QRes);
    ClearStack(&Stack1);
    ClearStack(&Stack2);
    return;
  }

  printf("Input an expression: ");
  GetStr(str, sizeof(str));
  Scanner(&Q, str);
  Parser(&QRes, &Q);
  printf("Result: %f\n", Eval(&QRes));
  _getch();
  ClearQueue(&QRes);
} /* End of 'Main' function */