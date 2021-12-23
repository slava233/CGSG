/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include <stdio.h>
#include <conio.h>

#include "expr.h"

void PrintTok( TOK T )
{
  if (T.Id == TOK_NUM)
    printf("Num: '%f'", T.Num);
  else if (T.Id == TOK_OP)
    printf("Op: '%c'", T.Op);
  else if (T.Id == TOK_NAME)
    printf("Variable: '%i'", T.Name[0]);
  else
    printf("Unknown token");
}

/* Push in stack function */
void Push( STACK *S, TOK T )
{
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    Error("No memory");
  NewElement->T = T;
  //NewElement->Next = NULL;
  NewElement->Next = S->Top; 
  S->Top = NewElement;
} /* End of 'Push' function */

/* Put in queue function */
void Put( QUEUE *Q, TOK T )
{
  LIST *NewElement;

  NewElement = malloc(sizeof(LIST));
  if (NewElement == NULL)
    Error("No memory");
  NewElement->T = T;
  NewElement->Next = NULL;
  if (Q->Head == NULL)
    Q->Head = Q->Tail = NewElement;
  else
    Q->Tail->Next = NewElement, Q->Tail = NewElement;
} /* End of 'Put' function */
                         
/* Start of get function */
BOOL Get( QUEUE *Q, TOK *T )
{
  LIST *Old;

  if (Q->Head == NULL)
    return 0;
  if (T != NULL)
    *T = Q->Head->T;
  Old = Q->Head;
  Q->Head = Q->Head->Next;
  free(Old);

  return 1;
}
/* End of get function */

/* Start of pop function */
BOOL Pop( STACK *S, TOK *T )
{
  LIST *Old;

  if (S->Top == NULL)
    return 0;
  if (T != NULL)
    *T = S->Top->T;
  Old = S->Top;
  S->Top = S->Top->Next;
  free(Old);
  return 1;
}
/* End of pop function */

/* Start of list displaying function */

void DisplayList( LIST *L )
{
  if (L == NULL)
    printf("Empty\n");
  else 
    while (L != NULL)
    {
      PrintTok(L->T);
      printf((L = L->Next) == NULL ? "\n" : ", ");
    }
}

/* End of list displaying function */

/* Start of clearing the list function */
void ClearList( LIST *L )
{
  LIST *N;

  while (L != NULL)
  {
    N = L;
    L = (*L).Next;
    free(N);
  } 
}
/* End of clearing the list function */

/* Start of queue displaying function */
void DisplayQueue( QUEUE *Q )
{
  DisplayList(Q->Head);
}
/* End of queue displaying function */

/* Start of stack displaying function */
void DisplayStack(STACK *S)
{
  DisplayList(S->Top);
}
/* End of stack displaying function */

/* Start of clearing the queue function */
void ClearQueue( QUEUE *Q )
{
  ClearList(Q->Head);
}
/* End of clearing the queue function */

/* Start of clearing the stack function */
void ClearStack( STACK *S )
{
  ClearList(S->Top);
}
/* End of clearing the stack function */

/* End of clearing the stack function */
void DropOpers( char Op )
{
  while (Stack2.Top != NULL && CheckAssoc(Stack2.Top->T.Op, Op))
  {
    TOK T;

    Pop(&Stack2, &T);
    Push(&Stack1, T);
  }
 }

INT GetPrior( char Op )
{
  switch (Op)
  {
  case '(':
    return 0;
  case ')':
    return 1;
  case ',':
    return 2;
  case '=':
    return 3;
  case '+':
  case '-':
    return 4;
  case '*':
  case '/':
  case '%':
    return 5;
  case '^':
    return 6;
  case '@':
    return 7;

  }
  Error("Unknown operator: '%c'", Op);
  return -1;
}
/* End of clearing the stack function */
