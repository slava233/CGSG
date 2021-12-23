#include <stdio.h>
#include <conio.h>

#define N 5

int P[N];

void Swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void Go(int Pos)
{
  int i;
  /*FILE *F = fopen("RES.TXT", "a");*/

  /*if (F == NULL)
    return;*/

  if (Pos == N)
    for (i = 0; i < N; i++)
    {
      /*f*/printf(/*F,*/ "%d", P[i]);
      if (i % N == N - 1)
        /*f*/printf(/*F,*/ "\n");
    }
  else
  {
    for (i = Pos; i < N; i++)
    {
      Swap(&P[Pos], &P[i]);
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
    }
  }
  /*fclose(F);*/
}

void main(void)
{
  int i;

  for (i = 0; i < N; i++)
    P[i] = i + 1;

  Go(0);

  _getch();
}