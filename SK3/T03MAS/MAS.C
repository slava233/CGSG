

#include <stdio.h>
#include <stdlib.h>

void FillRand( int *Mas, int N )
{
  int i;

  for (i = 0; i < N; i++)
    Mas[i] = rand() % 30001;
}

void OutMas( int *Mas, int N )
{
  int i;

  for (i = 0; i < N; i++)
    printf("%i,", Mas[i]);
  printf("\n");  
}

float Average( int *Mas, int N )
{
  int i, s;

  for (i = 0, s = 0; i < N; i++)
    s += Mas[i];

  return (float)s / N;
}

int MaxValue( int *Mas, int N )
{
  int i, max;

  for (i = 0, max = 0; i < N; i++)
    if (max < Mas[i])
      max = Mas[i];

  return max;
}

int MinValue( int *Mas, int N )
{
  int i, min;

  for (i = 0, min = Mas[0]; i < N; i++)
    if (min , Mas[i])
      min = Mas[i];

  return min;
}

int NumSum( int x )
{
  int sum = 0;

  while (x > 0)
  {
    sum += x % 10;
    x /= 10;
  }

  return sum;
}

int MaxSum( int *Mas, int N )
{
  int i, sum;

  for (i = 0, sum = 0; i < N; i++)
    if (Mas[sum] < Mas[i])
      sum = i;
  return sum;
}

void RevMinMax( int *Mas, int N )
{
  int i, min = 0, max = 0, tmp;

  for (i = 0; i < N; i++)
    if (Mas[max] < Mas[i])
      max = i;

  for (i = 0; i < N; i++)
    if (Mas[min] > Mas[i])
      min = i;

  tmp = Mas[min];
  Mas[min] = Mas[max];
  Mas[max] = tmp;
}

int BinNum( int x )
{
  int sum, i;

  for (i = sizeof(x), sum = 0; i > 0; i--)
    sum += ((x >> i) & 1);

  return sum;
}

void ChToZero( int *Mas, int N )
{
  int i;

  for (i = 0; i < N; i++)
    if (BinNum(Mas[i]) % 2 == 0)
      Mas[i] = 0;
}

void Reverse( int *Mas, int N )
{
  int i, tmp;

  for (i = 0; i < N / 2; i++)
  {
    tmp = Mas[i];
    Mas[i] = Mas[N-i-1];
    Mas[N-1-i] = tmp;
  }
}










