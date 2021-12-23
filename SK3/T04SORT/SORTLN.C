/* Kononov Svyatoslav 9-3 19.10.2018 */

#include <stdio.h>
#include "sort.h"

void QuickSort( DBL *a, int n )
{
  int b = 0, e = n - 1;
  DBL x = a[n / 2];

  if (n < 2)
    return;
  while (b <= e)
  {
    while (a[b] < x)
      b++;
    while (a[e] > x)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(&a[b], &a[e]);
      b++;
      e--;
    }
  }
  if (n < 2)
    return;
  QuickSort(a, e + 1);
  QuickSort(a + b, n - b);
}

void HeapCorrection( DBL *a, int n, int i )
{
  while (1)
  {
    int left = 2 * i + 1, right = 2 * i + 2;
    int big = i;

    if (left < n && a[left] > a[i])
      big = left;            
    if (right < n && a[right] > a[big])
      big = right;
    if (big == i)
      return;
    Swap(&a[i], &a[big]);
    i = big;
  }
}
void HeapSort( DBL *a, int n )
{
  int i = n / 2 - 1, k;

  for (i = n / 2 - 1; i >= 0; i--)
      HeapCorrection(a, n, i);
  for (k = n - 1;k >= 0; k--)
  {
    Swap(&a[0], &a[k]);
    for (i = k / 2 - 1; i >= 0; i--)
      HeapCorrection(a, k, i);
  }
}
static DBL *B;
                                                 
void MergeSortRec( DBL *a, int n )
{
  int M = n / 2, k = 0, j = M, i = 0;
  if (n < 2)
    return;
  MergeSortRec(a, M);
  MergeSortRec(a + M, n - M);

  for (k = 0; k < n; k++)
    if (j >= n || i < M && a[i] <= a[j])
      B[k] =a[i++];
    else
      B[k] = a[j++];
  memcpy(a, B, sizeof(DBL) * n);
}

void MergeSort( DBL *a, int n)
{
  B = malloc (sizeof(DBL) * n);
  if (B == NULL)
    return;
  MergeSortRec(a, n);
  free(B);
}



