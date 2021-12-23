/* Kononov Svyatoslav 9-3 19.10.2018 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>

#include "sort.h"

#define MAX 50000


void main(void)
{
  int si, fi;
  long t;
  void (*Fill[])(DBL *a, int n) =
  {
    FillRand, FillInc, FillDec, FillEq, FillMostly
  };
  
  void (*Sort[])(DBL *a, int n) =
  {
    BubbleSort1, BubbleSort2, SelectionSort, InsertionSort, ShakerSort, QuickSort, HeapSort, MergeSort
  };
  char *SortName[] = 
  {
    "BubbleSort1", "BubbleSort2", "SelectionSort", "InsertionSort", "ShakerSort","QuickSort", "HeapSort", "MergeSort"
  };
  void *FillName[] =
  {
    "Rand", "Inc", "Dec", "Eq", "Mostly"
  };
  static DBL mas[MAX];

  for (fi = 0; fi < sizeof(Fill) / sizeof(Fill[0]); fi++)
    printf("%12s", FillName[fi]);
  printf("\n");
  for (si = 0; si < sizeof(Sort) / sizeof(Sort[0]); si++)
  {
    printf("Sort is: %s\n", SortName[si]);
    for (fi = 0; fi < sizeof(Fill) / sizeof(Fill[0]); fi++)
    {
      Fill[fi](mas, MAX);
      t = clock();
      Sort[si](mas, MAX);
      t = clock() - t;
      if(CheckSort(mas, MAX))
        printf(" %10.5f ", t / (DBL)CLOCKS_PER_SEC);
      else
        printf("    Fail    ");
    }
    printf("\n");
  }
  _getch();
}
