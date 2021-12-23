#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "dsort.h"

#define MAX_DIGITS 256

void Out( ull *A, int N )
{
  int i;

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  WORD saved_attributes;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

  for (i = 0; i < N; i++)
    printf("%llu  ", A[i]);

  SetConsoleTextAttribute(hConsole, saved_attributes);
}

void Fill( ull *A, int N, int R )
{
  int i;

  for (i = 0; i < N; i++)
    A[i] = (ull)rand(R) * rand(R) * (rand(R) + rand(R)); 
}

void SwapULPtr( ull **A, ull **B )
{
  ull *tmp = *A;

  *A = *B;
  *B = tmp;
}

static ull *B;
void DigitalSort( ull *A, int N )
{
  int Count[MAX_DIGITS], Offset[MAX_DIGITS];
  int i, flag = 1, parity = 0, k;

  B = malloc(sizeof(ull) * N);
  if (B == NULL)
    return;

  for (k = 0; k < 8; k++)
  {
    for (i = 0; i < MAX_DIGITS; i++)
      Count[i] = 0;

    for (i = 0; i < N; i++)
      Count[((uchar *)&A[i])[k]]++;

    Offset[0] = 0;
    for (i = 1; i < MAX_DIGITS; i++)
      Offset[i] = Offset[i - 1] + Count[i - 1];

    for (i = 0; i < N; i++)
      B[Offset[((uchar *)&A[i])[k]]++] = A[i];

    SwapULPtr(&A, &B);
    parity = !parity;
  }

  if (parity)
    SwapULPtr(&A, &B);

  free(B);
 }