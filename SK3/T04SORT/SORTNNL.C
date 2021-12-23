/* Kononov Svyatoslav 9-3 19.10.2018 */

#include <stdio.h>
#include "sort.h"

void ShakerSort( DBL *a, int n )
{
  int i, last = n - 2, first = 0, last_changed;

  do
  {
    for (i = last, last_changed = last; i >= first; i--)
      if (a[i] > a[i + 1])
        Swap(&a[i], &a[i + 1]), last_changed = i;
    first = last_changed + 1;

    for (i = first, last_changed = 0; i <= last; i++)
      if (a[i] > a[i + 1])
        Swap(&a[i], &a[i + 1]), last_changed = i;
    last = last_changed - 1;
  } while (last >= first);      
}

int CheckSort( DBL *a, int n )
{
  int i;

  for (i = 0; i < n - 1; i++)
    if(a[i] > a[i + 1])
      return 0;
  return 1;
}
void BubbleSort1( DBL *a, int n )
{
  int i, k;

  for (k = 0; k < n - 1; k++)
    for (i = 0; i < n - k - 1; i++)
      if (a[i] > a[i + 1])
        Swap(&a[i], &a[i + 1]);
} 
void BubbleSort2( DBL *a, int n)
{
  int i, last = n - 2, last_changed;

  do
  {
    for (last_changed = 0, i = 0; i <= last; i++)
      if(a[i] > a[i + 1])
        Swap(&a[i], &a[i + 1]), last_changed = i;
    last = last_changed - 1;
  }while (last >= 0);
}
void InsertionSort( DBL *a, int n )
{
  int i, j; 
  DBL x;

  for (i = 1; i <= n - 1; i++)
  {
    x = a[i];
    j = i - 1;
    while (j >= 0 && a[j] > x)
      a[j + 1] = a[j], j--;
    a[j + 1] = x;
  }          
}
void SelectionSort( DBL *a, int n)
{
  int i, j, min;

  for (j = 0; j < n - 1; j++)
  {
    for (min = j, i = j + 1; i < n; i++)
      if (a[i] < a[min])
        min = i;
    Swap(&a[j], &a[min]);
  }
}
