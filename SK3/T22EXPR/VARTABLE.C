/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include <string.h>

#include "expr.h"

typedef struct tagVARLIST VARLIST;
struct tagVARLIST
{
  char Name[MAX_NAME];
  double Value;
  VARLIST *Next;                                       
} *VarTable = NULL;

void SetValue( char *Name, double Value )
{
  VARLIST **ptr = &VarTable;

  while (*ptr != NULL)
    if (strcmp((*ptr)->Name, Name) == 0)
    {
      (*ptr)->Value = Value;
      return;
    }
    else 
      ptr = &(*ptr)->Next;
  if ((*ptr = malloc(sizeof(VARLIST))) == NULL)
    Error("Not enough room for new variable");
  strncpy((*ptr)->Name, Name, MAX_NAME - 1);
  (*ptr)->Value = Value;
  (*ptr)->Next = NULL;
}

void DisplayVarTable( void )
{
  VARLIST **ptr = &VarTable;

  while (*ptr != NULL)
  {
    printf("%s: %f  ", (*ptr)->Name, (*ptr)->Value);
    ptr = &(*ptr)->Next;
  }
  printf("\n"); 
}

double GetValue( char *Name )
{
  VARLIST **ptr = &VarTable;

  while (*ptr != NULL)
  {
    if (strcmp((*ptr)->Name, Name) == 0)
      return (*ptr)->Value;
    else 
      ptr = &(*ptr)->Next;
    DisplayVarTable();
  }
  return 0;
} 

void ClearVarTable( void )
{
  VARLIST **ptr = &VarTable;
  VARLIST *ptr1;

  while (*ptr != NULL)
  {
    ptr1 = *ptr;
    ptr = &(*ptr)->Next;
    free(ptr1);
  }
}

int CheckAssoc( char Op1, char Op2 )
{
  INT p1 = GetPrior(Op1), p2 = GetPrior(Op2);
  if (Op2 == '=')
    return p1 > p2;
  return p1 >= p2;
}