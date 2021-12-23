#include <stdio.h>
#include <time.h>

#include "dsort.h"

int main( void )
{
  static ull mas[MAX];
  long long t;
  int R;

  scanf("%i", &R);
  Fill(mas, MAX, R);
  t = clock();
  DigitalSort(mas, MAX);
  t = clock() - t;
  Out(mas, MAX);
  printf(" %10.5f ", t / (DBL)CLOCKS_PER_SEC);
  _getch();
  return 0;
}
