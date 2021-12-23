#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "FUR.H"

#define MAX_STR 111

typedef struct tagTREE TREE;
struct tagTREE
{
  char Text[MAX_STR];
  TREE *No, *Yes;
};

void Menu( void )
{
  printf("0 - exit\n"
         "1 - session\n"
         "2 - draw tree\n"
         "3 - save\n"
         "4 - load\n\n");
}

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

TREE * Init( char *Text, TREE *N, TREE *Y )
{
  TREE *T = malloc(sizeof(TREE));

  if (T == NULL)
    return NULL;
  strncpy(T->Text, Text, MAX_STR - 1);
  T->No = N;
  T->Yes = Y;
  return T;
}

void Session( TREE **T )
{
  char Ans[MAX_STR], Qst[MAX_STR], key;
  
  if (*T == NULL) 
    return;

  while (1)
  {
    printf("%s?", (*T)->Text);
    key = _getch();

    if (key == 'Y' || key == 'y')
      printf(" Yes\n");
    else
      printf(" No\n");

    if ((*T)->Yes != NULL)
    {
      if (key == 'Y' || key == 'y')
      {
        T = &(*T)->Yes;
        return;
      }
      else
        T = &(*T)->No;
    }
    else
    {
      printf("Тогда введите новое определение:");
      GetStr(Qst, MAX_STR);
      printf("Введите правильный ответ для определения:");
      GetStr(Ans, MAX_STR);
      *T = Init(Qst, *T, Init(Ans, NULL, NULL));
      return;
    }
  }
}

void SaveTreeRec( FILE *F, TREE *T )
{
  if (T == NULL)
    return;
  fwrite(T, sizeof(TREE), 1, F);
  SaveTreeRec(F, T->No);
  SaveTreeRec(F, T->Yes);
}

int SaveTree( char *FileName, TREE *T )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  SaveTreeRec(F, T);

  fclose(F);
  return 1;
}

void LoadTreeRec( FILE *F, TREE **T )
{
  TREE tr;

  if (fread(&tr, sizeof(TREE), 1, F) != 1)
    return;

  *T = Init(tr.Text, NULL, NULL);

  if (tr.No != NULL)
    LoadTreeRec(F, &(*T)->No);
  if (tr.Yes != NULL)
    LoadTreeRec(F, &(*T)->Yes);
}

int LoadTree( char *FileName, TREE **T )
{
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;

  LoadTreeRec(F, T);

  fclose(F);
  return 1;
}

void DrawTree( TREE *T, int Level )
{
  if (T != NULL)
  {
    DrawTree(T->Yes, Level + 1);
    printf("%*c%d", Level * 3, ' ', T->Text);
    DrawTree(T->No, Level + 1);
  }
}

void main( void )
{
  TREE *ExSys;

  system("chcp 1251");

  SetDbgMemHooks();

  ExSys = Init("чё не цгшник", NULL, NULL);

  Menu();
  
  switch(_getch())
  {
  case '0':
    exit(0);
  case '1':  
    Session(&ExSys);
  case '2': 
    DrawTree(ExSys, 1);
  case '3':
    SaveTree("TREE.TXT", ExSys);
  case '4':  
    LoadTree("TREE.TXT", &ExSys);
  }
}

