#include <stdio.h>
#include <string.h>

#include "headers.h"

DBL LatentTime[3] = {2, 2, 2};

BYTE AvaX, AvaY;
ENEMY Enemies[MAX_ENEMIES];
BYTE Lab[MAX][MAX];
static int NumOfEnemies;

/* The Load-the-lab function */
void LabLoad( char *FileName )
{
  FILE *F;
  int X = 0, Y = 0, ch;

  if ((F = fopen(FileName, "r")) != NULL)
  {
    memset(Lab, 0, sizeof (Lab));
    while ((ch = fgetc(F)) != EOF)
    {
      switch (ch)
      {
      case ' ':
        Lab[Y][X] = 0;
        break;
      case '*':
        Lab[Y][X] = 1;
        break;
      case 'a':
        Lab[Y][X] = 0;
        AvaX = X;
        AvaY = Y;
        break;
      case 'e':
        Lab[Y][X] = 0;
        if (NumOfEnemies < MAX_ENEMIES)
          {
            Enemies[NumOfEnemies].X = X;
            Enemies[NumOfEnemies].Y = Y;
            Enemies[NumOfEnemies].DeltaTime = 0;
            NumOfEnemies++;
          }
          break;
      case '\n':
          Y++, X = 0;
          break;
      }
      if (X < MAX)
        X++;
      else
        if (Y < MAX)
          Y++, X = 0;
        else
          break;
    }
  }
} /* End of 'LoadLab' function */

/* The Check function */
BYTE GetCell( BYTE A[MAX][MAX], int x, int y )
{
  if (x < 0 || y < 0 || x >= MAX || y >= MAX || Lab[y][x] == 1)
    return INFINITY;
  return A[y][x];
} /* End of 'GetCell' function */

/* The Draw function */
void DrawPlace( void )
{
  int i, j;   

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      if (Lab[i][j] == 1)
        PutPixel(j, i, 0x0000FF);
      else
        PutPixel(j, i, 0);

  PutPixel(AvaX, AvaY, 0x00FF00); 

  for (i = 0; i < NumOfEnemies; i++)
  {
    PutPixel(Enemies[i].X, Enemies[i].Y, 0xFF0000);
    BrainEnemies();
  }
  for (i = 0; i < NumOfEnemies; i++)
    if (Enemies[i].X == AvaX && Enemies[i].Y == AvaY)
      exit(0);
} /* End of 'DrawPlace' function */

/* The move function */
void Strategy( ENEMY *E )
{
  int x, x1, y, y1, len, n, d, flag;
  static int GoToX[4] = {-1, 0, 1, 0},
             GoToY[4] = {0, 1, 0, -1};

  for (y = 0; y < MAX; y++)
    for (x = 0; x < MAX; x++)
      E->Solution[y][x] = INFINITY;

  E->Solution[AvaY][AvaX] = 0;

  do
  {
    flag = 0;
    for (y = 0; y < MAX; y++) 
      for (x = 0; x < MAX; x++)
        if (Lab[y][x] == 0)
        {
          len = INFINITY;
          for (d = 0; d < 4; d++)
            if ((n = GetCell(E->Solution, x + GoToX[d], y + GoToY[d])) != INFINITY && n < len)
              len = n;
          if (E->Solution[y][x] > len + 1)
            E->Solution[y][x] = len + 1, flag = 1;
        }
  } while (flag);

  x1 = x = E->X;
  y1 = y = E->Y;
  len = E->Solution[y][x];
  for (d = 0; d < 4; d++)
    if ((n = GetCell(E->Solution, x + GoToX[d], y + GoToY[d])) != INFINITY && n < len)
    {
      x1 = x + GoToX[d];
      y1 = y + GoToY[d];
      len = n;
    }
  
  E->X = x1;
  E->Y = y1;
} /* End of 'Strategy' function */

/* The Inspector of Enemies function */
void BrainEnemies( void )
{
  int i;

  for (i = 0; i < NumOfEnemies; i++)
  {
    Enemies[i].DeltaTime += DeltaTime;
    if (Enemies[i].DeltaTime > LatentTime[i])
    {
      Enemies[i].DeltaTime = 0;

      Strategy(&Enemies[i]);
    }
    if (AvaX == Enemies[i].X && AvaY == Enemies[i].Y)
      GAME_OVER = 1;
  }
} /* End of 'BrainEnemies' function */

