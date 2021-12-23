/* Kononov Svyatoslav, 09-3, 07.12.2018 */

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
        if (B.Id == TOK_NAME && T.Op != ',')  /**/
          B.Num = GetValue(B.Name); 
      }
      Pop(&S, &A);
      if (A.Id == TOK_NAME && T.Op != '=')
        A.Num = GetValue(A.Name);
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
  printf("Result: %lf", A.Num);
  return A.Num;
} /* End of 'Eval' function */

/* END OF 'EVAL.C' FILE */
