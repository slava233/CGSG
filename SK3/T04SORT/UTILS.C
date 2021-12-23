/* Kononov Svyatoslav 9-3 19.10.2018 */

#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
DBL R0( void )
{
  return (DBL)rand() / RAND_MAX;
}

DBL R1( void )
{
  return 2.0 * (DBL)rand() / RAND_MAX;
}

void Swap( DBL *x, DBL *y )
{
  DBL tmp = *x;

  *x = *y;
  *y = tmp;
}

void FillRand( DBL *a, int n )
{
  int i;

  srand(30);
  for (i = 0; i < n; i++)
    a[i] = 30 * (2.0 * rand() / RAND_MAX - 1);
}

void FillInc( DBL *a, int n )
{
  int i;

  for (srand(30), a[0] = 102 * R1(), i = 1; i < n; i++)
    a[i] = a[i - 1] + R0() *30;
}

void FillDec( DBL *a, int n )
{
  int i;

  for (srand(30), a[0] = 102 * R1(), i = 1; i < n; i++)
    a[i] = a[i - 1] - R0() *30;
}

void FillEq( DBL *a, int n )
{
  int i;

  for (srand(30), a[0] = 78 * R1(), i = 1; i < n; i++)
    a[i] = a[0];
}

void FillMostly( DBL *a, int n )
{
  int i;

  FillInc(a, n);
  for (i = 0; i < n / 20; i++)
    Swap(&a[rand() % n], &a[rand() % n]);
}

void OutMas( DBL *a, int n )
{
  int i;

  for (i = 0; i < n; i++)
    printf("%f%c", a[i], i != n - 1 ? ',' : '\n');
}