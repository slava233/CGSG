/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include <math.h>

#include "expr.h"

STACK StackEval;

/* Evaluate function */
double Eval( QUEUE *Q )
{
  STACK S = {NULL};
  TOK T, A = {0}, B = {0};

  while (Get(Q, &T))
  {
    if (T.Id == TOK_NUM || T.Id == TOK_NAME)
      Push(&S, T);
    else 
    {
      if (T.Op != '@')
      {
        Pop(&S, &B);
        if (B.Id == TOK_NAME)
          B.Num = GetValue(B.Name);
      }
      Pop(&S, &A);
      if (A.Id == TOK_NAME && T.Op != '=')
        A.Num = GetValue(A.Name), A.Id = TOK_NUM;
      switch (T.Op)
      {
      case '+':
        A.Num += B.Num;
        break;
      case '-':
        A.Num -= B.Num;
        break;
      case '*':
        A.Num *= B.Num;
        break;
      case '/':
        A.Num /= B.Num;
        break;
      case '^':
        A.Num = pow(A.Num, B.Num);
        break;
      case '%':
        A.Num = fmod(A.Num, B.Num);
        break;
      case '@':
        A.Num = -A.Num;
        break;
      case '=':
        if (A.Id != TOK_NAME)
          Error("LValue required!\n)");
        SetValue(A.Name, B.Num);
        A.Id = TOK_NUM;
        A.Num = B.Num;
        break;
      case ',':
        A.Id = TOK_NUM;
        A.Num = B.Num;
        break;
      } 
      Push(&S, A);
    }
  }
  Pop(&S, &T);
  DisplayVarTable();
  return A.Num;
} /* End of Evaluate function */

