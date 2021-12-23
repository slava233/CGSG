#include <stdio.h>
#include <conio.h>

#define MAX 100

typedef struct
{
  int DAY, MONTH, YEAR;
} DATE;

typedef struct
{ 
  char NAME[30];
  char SURNAME[47];
  DATE BIRTHDAY;
  char SEX;
  int HOURS[7];
} WORKER;

typedef unsigned char uchar;

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

void ReadWorker( WORKER *W )
{
  printf("Name:\n");
  GetStr(W->NAME, sizeof W->NAME);
  printf("Surname:\n");
  GetStr(W->SURNAME, sizeof W->SURNAME);
  printf("BirthDay:\n");
  scanf("%d", &W->BIRTHDAY.DAY);
  GetStr(NULL, 0);
  printf("BirthMonth:\n");
  scanf("%d", &W->BIRTHDAY.MONTH);
  GetStr(NULL, 0);
  printf("BirthYear:\n");
  scanf("%d", &W->BIRTHDAY.YEAR);
  GetStr(NULL, 0);
  printf("Sex:\n");
  GetStr(W->SEX, sizeof W->SEX); 
  printf("Hours in Monday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Tuesday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Wednesday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Thursday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Friday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Saturday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
  printf("Hours in Sunday:\n");
  GetStr(W->HOURS, sizeof W->HOURS);
}

int SaveDB( char *FileName, WORKER *Base, int N )
{
  FILE *F;
  if ((F = fopen(FileName, "wb") == NULL))
    return 0;
  fwrite(Base, sizeof(WORKER), N, F);
  fclose(F);
  return 1;
}

int LoadDB( char *FileName, WORKER *Base, int MaxSize )
{
  int N;
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  N = fread(Base, sizeof(WORKER), MaxSize, F);
  fclose(F);
  return N;
}

/*void Sort( WORKER *A, int N, int (*IsNameLess)( WORKER A, WORKER B ))
{

  if (IsNameLess(A[i], A[j]))

}

int IsNameLess( WORKER A, WORKER B )
{
  int n = strcmp(A.SURNAME, B.SURNAME);
  if (n == 0)
    return strcmp(A.NAME, B.NAME);
  return n;
}

int IsDateLess( WORKER A, WORKER B )
{ 
  if (A.BIRTHDAY.YEAR == B.BIRTHDAY.YEAR)
    if (A.BIRTHDAY.MONTH == B.BIRTHDAY.MONTH)
      if (A.BIRTHDAY.DAY == B.BIRTHDAY.DAY)
        return A.BIRTHDAY = B.BIRTHDAY;
      else
        if (A.BIRTHDAY.DAY > B.BIRTHDAY.DAY)
          return A.BIRTHDAY.DAY > B.BIRTHDAY.DAY;
        else
          return A.BIRTHDAY.DAY < B.BIRTHDAY.DAY;
    else
      if (A.BIRTHDAY.MONTH < B.BIRTHDAY.MONTH)
        return A.BIRTHDAY.MONTH < B.BIRTHDAY.MONTH;
      else
        return A.BIRTHDAY.MONTH > B.BIRTHDAY.MONTH;
  else 
    if (A.BIRTHDAY.YEAR < B.BIRTHDAY.YEAR)
      return A.BIRTHDAY.YEAR < B.BIRTHDAY.YEAR;
    else
      return A.BIRTHDAY.YEAR > B.BIRTHDAY.YEAR;
}*/

void main( void )
{
  int DBSize = 0, i;
  static WORKER DB[MAX];
  char fname;
  printf("0 - exit\n");
  printf("1 - input new worker\n");
  printf("2 - output all workers\n");
  printf("3 - delete worker by number\n");
  printf("4 - sort\n");
  printf("5 - \n");
  printf("6 - save\n");
  printf("7 - load\n");
  printf("8 - change worker base by number\n");
  printf("9 - input\n"); 

  switch(getch())
  {
    case '0':
      break;
    case '1':
      if (DBSize < MAX)
        ReadWorker(&DB[DBSize++]);
      else           
        printf("Not enough room\n");
      break;
    case '2':
      for (i = 0; i < DBSize; i++)
        printf("%i) %s %s\n", i, DB[i].SURNAME, DB[i].NAME);
      break;
    /*case '4':
      printf("Sort by: \n Surname + Name - a \n Birthday - b\n");
      switch(getch())
      {
      case 'a':
        Sort(DB, DBSize, IsNameLess);
        break;
      case 'b':
        Sort(DB, DBSize, IsDateLess);
        break;
      }*/
    case '6':
      printf("Save file name:\n");
      GetStr(fname, sizeof(fname));
      if (SaveDB(fname, DB, DBSize))
        printf("Ok\n");
      else
        printf("Error\n");
      break;
    case '7':
      printf("Load file name:\n");
      GetStr(fname, sizeof(fname));
      DBSize = LoadDB(fname, DB, MAX);
      printf("Load %d records\n", DBSize);
      break;
  }
}