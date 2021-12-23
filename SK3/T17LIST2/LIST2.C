/* Kononov Svyat 9-3 19.11.2018 */

#include "LIST2.h"

/* Start of Display function */
void ListDisplay(LIST *L)
{
  if (L == NULL)
    printf("<Empty list>\n");
  else
  {
    LIST *S = L;
    while (L->Prev != NULL)
      L = L->Prev;
    while (L != NULL)
    {
      printf("%s%s", L->Str, L == S ? "(*)" : "");
      printf("%c", (L = L->Next) == NULL ? '\n' : ',');
    }
    printf("\n");
  }
}
/* End of Display function */

void ShiftNext(LIST **L)
{
  if (*L != NULL && (*L)->Next != NULL)
    *L = (*L)->Next;
}

void ShiftPrev(LIST **L)
{
  if (*L != NULL && (*L)->Prev != NULL)
    *L = (*L)->Prev;
}

/* Start of Adding To Front function */
int ListAddToFront(LIST **L, int NewData)
{
  LIST *New = malloc(sizeof(LIST));

  if (New == NULL)
    return 0;

  New->Data = NewData;
  New->Next = *L;
  *L = New;

  return 1;
}
/* End of Adding To Front function */

/* Start of Clear function*/
void ClearList(LIST **L)
{
  LIST *N;

  while (*L != NULL)
  {
    N = *L;
    *L = (*L)->Next;
    free(N);
  } 
}
/* End of Clear function*/

/* Start of Deleting From Front function */
int ListDelFromFront(LIST **L)
{
  LIST *SAVE = (*L)->Next;

  if (*L == NULL)
    return 0;

  free(*L);
  *L = SAVE;

  return 1;
}
/* End of Deleting From Front function */

/* Start of Adding To Back function */
int ListAddToBack(LIST **L, int NewData)
{
  while (*L != NULL)
    L = &(*L)->Next;
  if ((*L = malloc(sizeof(LIST))) == NULL)
    return 0;

  (*L)->Data = NewData;
  (*L)->Next = NULL;
  return 1;
}
/* End of Adding To Back function */

/* Start of Deleting From Back function */
int ListDelFromBack(LIST **L)
{
  if (*L == NULL)
    return 0;

  while ((*L)->Next != NULL)
    L = &(*L)->Next;

  free(*L);
  *L = NULL;

  return 1;
}
/* End of Deleting From Back function */

/* End of LIST.c file */