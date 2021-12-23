#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 9
#define INFINITY 10000

int Adj[MAX][MAX], Path[MAX], Was[MAX] = {0}, PathLen = 0, Best[MAX], BestPathLen = 0, From[MAX], Len[MAX];

void LabLoad( void )
{
  int a, b, i, j, n, len;
  FILE *F;

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      Adj[i][j] = INFINITY;

  if ((F = fopen("LAB3.TXT", "r")) != NULL)
  {
    do
    {
      n = fscanf(F, "%d%d%d", &a, &b, &len);
      if (n == 2)
        len = 1;
      Adj[a][b] = Adj[b][a] = len;
    } while (n > 1);
  }
}

void Display( void )
{
  int i;
  
  system("cls");
  for (i = 0; i < PathLen; i++)
  {
    printf("%d", Path[i]);
    printf("\n");
  }
}

/* Step check function */
int Go( int A, int B )
{
  int i;

  if (Adj[A][B] == 1)
  {
    if (BestPathLen == 0 || PathLen < BestPathLen)
    {
      BestPathLen = PathLen;
      memcpy(Best, Path, sizeof(int) * PathLen);
    }
    /* Display(); */
    return 1; 
  }
  for (i = 0; i < MAX; i++)
  {
    if (i != A && i != B && Was[i] == 0 && Adj[A][i] != 0)
    {
      Was[i] = 1;
      Path[PathLen++] = i;

      if (Go(i, B))
        ;
      PathLen--;
      Was[i] = 0;
    }
  }
  return 0;
} /* End of 'go' function */

void Go2( int A, int B )
{
  int i, j, flag, Len1[MAX], From1[MAX];

  for (i = 0; i < MAX; i++)
  {
    Len1[i] = INFINITY;
    From1[i] = -1;
  }

  Len1[B] = 0;

  do 
  {
    flag = 0;
    memcpy(Len, Len1, sizeof (int) * MAX);
    memcpy(From, From1, sizeof (int) * MAX);
    for (i = 0; i < MAX; i++)
      for (j = 0; j < MAX; j++)
        if (Adj[i][j] != 0 && Len[i] > Len[j] + Adj[i][j])
        {
          Len1[i] = Len[j] + Adj[i][j];
          From1[i] = j;
          flag = 1;
        }
  } while (flag);
  memcpy(Len, Len1, sizeof (int) * MAX);
  memcpy(From, From1, sizeof (int) * MAX); 
}

void main ( void )
{
  int b, e, i;
  /* FILE *F; */
  LabLoad();
  scanf("%i%i", &b, &e); 
  Was[b] = 1;
  Go2(b, e);
  if (From[b] == -1)
    printf("Not find a way");
  else
    do
    {
      printf("%i ", b);
      b = From[b];
    } while (b != -1);
  /* system("cls");
   * for (i = 0; i < BestPathLen; i++)
   * {
   *   printf("%d", Best[i]);
   *   printf("\n");
   * }
   * if ((F = fopen("LABDONE.TXT", "a")) != NULL)
   * {
   *   fprintf(F, "From %d to %d\n", b, e);
   *   for (i = 0; i < BestPathLen; i++)
   *   { 
   *     fprintf(F, "%d", Best[i]);
   *     fprintf(F, "\n");
   *   }
   * } */
  _getch();
}

/* END OF 'T14LAB2D.C' FILE*/
