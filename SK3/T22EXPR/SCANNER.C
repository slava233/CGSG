/* Kononov Svyatoslav, 09-3, 07.12.2018 */

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "expr.h"


/* Scan string function */
int Scanner( QUEUE *Q, CHAR *S )
{
  TOK T = {0};
  int i;

  while (*S != 0)
  {
    switch (*S)
    {
    case ' ':
    case '\n':
      S++;
      continue;
    case '+':
    case '-':
    case '/':
    case '*':
    case '%':
    case '^':
    case '=':
    case '(':
    case ')':
    case ',':
      T.Id = TOK_OP;
      T.Op = *S++;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      T.Id = TOK_NUM;
      T.Num = 0;
      while (isdigit(*S))
        T.Num = T.Num * 10 + *S++ - '0';
      if (*S == '.')
      {
        double denum = 1;
        S++;
        while (isdigit(*S))
          T.Num += (*S++ - '0') / (denum *= 10);
      }
      break;
    default:
      if (isalpha((BYTE)*S))
      {
        T.Id = TOK_NAME;
        i = 0;
        do
        {
          if (i < MAX_NAME - 1)
            T.Name[i++] = *S;
          S++;
        } while (isalpha((BYTE)*S) || isdigit((BYTE)*S));
        T.Name[i] = 0;
        break;
      }
      Error("Unrecognized character '%c'\n", *S);
    }
    Put(Q, T);
  }
  return 1;
} /* End of 'Scanner' function */

/* END OF 'SCANNER.C' FILE */