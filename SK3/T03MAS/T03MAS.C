/* Shayda Andrey, 09-4, 03.10.2018 */

#include <stdio.h>
#include <conio.h>

#include "MAS.H"

#define MAX 8

void main( void )
{
  int A[MAX];

  FillRand(A, MAX);
  OutMas(A, MAX);
  ChToZero(A, MAX);
  OutMas(A, MAX);
  Reverse(A, MAX);
  OutMas(A, MAX);
  printf("Max element number is %i\n", MaxSum(A, MAX) + 1);

  _getch();
}