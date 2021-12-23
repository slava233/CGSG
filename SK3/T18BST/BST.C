/* Kononov Svyat 9-3 19.11.2018 */

#include <stdio.h>

#include "BST.H"

int SearchTree( TREE *T, int Key )
{
  if (T == NULL)
    return 0;
  if (T->Key == Key)
    return 1;
  if (T->Key < Key)
    return SearchTree(T->More, Key);
  return SearchTree(T->Less, Key); 
}

int SearchTree1( TREE *T, int Key )
{
  while (T != NULL && T->Key != Key)
  {
    if (T->Key < Key)
      T = T->More;
    else
      T = T->Less;
  }
  return T != NULL;
}

int AccessRecTree( TREE **T, int Key )
{
  if (*T == NULL)
  {
    *T = malloc(sizeof(TREE));
    if (*T == NULL)
    {
      printf("\nNot enough space\n\n");
      return 0;
    }
    (*T)->Key = Key;
    (*T)->Less = (*T)->More = NULL;
    printf("\nAdd a new node\n\n");
    return 1;
  }
  if ((*T)->Key == Key)
  {
    printf("\nKey %i is found\n\n", Key);
    return 1;
  }
  if ((*T)->Key < Key)
    return AccessRecTree(&(*T)->More, Key);
  return AccessRecTree(&(*T)->Less, Key);
}

int AccessNonRecTree( TREE **T, int Key )
{
  return 0;
}

void PutTree( TREE *T )
{
  if (T == NULL)
    printf("*");
  else
  {
    printf("%d)", T->Key);
    PutTree(T->Less);
    printf(",");
    PutTree(T->More);
    printf(")");
  }
}

void PutTree2( TREE *T )
{
  if (T == NULL)
    printf("*");
  else
  {
    printf("%d)", T->Key);
    PutTree(T->Less);
    printf(",");
    PutTree(T->More);
    printf(")");
  }
}

void DrawTree( TREE *T, int Level )
{
  if (T != NULL)
  {
    DrawTree(T->More, Level + 1);
    printf("%*c%d", Level * 3, ' ', T->Key);
    DrawTree(T->Less, Level + 1);
  }
}

void ClearTree( TREE **T )
{
  if (*T != NULL)
  {
    ClearTree(&(*T)->Less);
    ClearTree(&(*T)->More);
    free(*T);
    *T = NULL;
  }
}
