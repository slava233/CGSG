/* Kononov Svyatoslav 9-3 07.12.2018 */

#include <stdio.h>
#include <stdlib.h>

#include "QUST.H"

/* Start of push function */
int Push(STACK *S, int NewData)
{
  LIST *New = malloc(sizeof(LIST));

  New->Data = NewData;
  New->Next = S->Top;
  
  S->Top = New;

  return 1;
}
/* End of push function */

/* Start of put function */
int Put(QUEUE *Q, int NewData)
{
  LIST *New = malloc(sizeof(LIST));
  
  New->Data = NewData;
  New->Next = NULL;

  if (Q->Head == NULL)
    Q->Head = Q->Tail = New;
  else
    Q->Tail->Next = New, Q->Tail = New;

  Q->Tail = New;
  return 1;
}
/* End of put function */
                         
/* Start of get function */
int Get(QUEUE *Q)
{
  LIST *SAVE = malloc(sizeof(LIST));
  SAVE = Q->Head->Next;

  if (Q == NULL)
    return 0;

  free(Q->Head);
  Q->Head = SAVE;

  return 1;
}
/* End of get function */

/* Start of pop function */
int Pop(STACK *S)
{
  LIST *SAVE = malloc(sizeof(LIST));
  SAVE = S->Top->Next;

  if (S == NULL)
    return 0;

  free(S->Top);
  S->Top = SAVE;

  return 1;
}
/* End of pop function */

/* Start of list displaying function */
void DisplayList(LIST *L)
{
  if (L == NULL)
    printf("<Empty list>\n");
  else
    while (L != NULL)
    {
      printf("%d", L->Data);
      printf("%c", (L = L->Next) == NULL ? '\n' : ',');
    }
    printf("\n");
}
/* End of list displaying function */

/* Start of clearing the list function */
void ClearList(LIST *L)
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
void DisplayQueue(QUEUE *Q)
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
void ClearQueue(QUEUE *Q)
{
  ClearList(Q->Head);
}
/* End of clearing the queue function */

/* Start of clearing the stack function */
void ClearStack(STACK *S)
{
  ClearList(S->Top);
}
/* End of clearing the stack function */

/* End of QUST.C file */

