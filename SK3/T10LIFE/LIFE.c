#include <glut.h>
#include <stdlib.h>
#include <string.h>

#include "life.h"

byte f1[H * W], f2[H * W];

void DrawField( byte *F )
{
  int x, y;
  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
      if (GetCell(F, x, y))
        PutPixel(x, y, 666666 * rand());
      else
        PutPixel(x, y, 0);
}

void NewGeneration( byte *f1, byte *f2 )
{
  int x, y, value = 0, n;

  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      n = GetNeighbours(f1, x, y);
      if (GetCell(f1, x, y))
      {
        if (n < 2 || n > 3)
          value = 0;
        else
          value = 1;
      }
      else
      {
        if (n == 3)
          value = 1;
        else
          value = 0;
      }
      SetCell(f2, x, y, value);
    }
}

int GetNeighbours( byte *F, int x, int y )
{
  return GetCell(F, x - 1, y + 1) + GetCell(F, x, y + 1) + GetCell(F, x + 1, y + 1) + GetCell(F, x - 1, y) + GetCell(F, x + 1, y) + GetCell(F, x - 1, y - 1) + GetCell(F, x, y - 1) + GetCell(F, x + 1, y - 1);
}

int GetCell( byte *F, int x, int y )
{
  x = (x + W) % W;
  y = (y + H) % H;
  return F[y * W + x];
}

void LifeInit( void )
{
  FieldInit(f1);
}

void LifeStep( void )
{
  NewGeneration(f1, f2);
  DrawField(f2);
  memcpy(f1, f2, sizeof(f1));
}

void SetCell( byte *F, int X, int Y, int value )
{
  X = (X + W) % W;
  Y = (Y + H) % H;
  F[Y * W + X] = value;
}

void FieldInit( byte *F )
{
  int X, Y;

  srand(30);

  for (X = 0; X < H; X++)
    for (Y = 0; Y < W; Y++)
      F[W * Y + X] = rand() % 3;
}

/*void Begun( byte *F )
{
  int n = 3000;
  while (n--)
  {
    int a, j, x;  
  }
}*/
