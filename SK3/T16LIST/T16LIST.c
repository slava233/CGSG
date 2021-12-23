/* Kononov Svyat 9-3 16.11.2018 */

#include <stdio.h>
#include <conio.h>

#include "LIST.h"

/* Start of Menu function */
void Menu(void)
{
  printf("0 - ext\n"
         "1 - add to front\n"
         "2 - del from front\n"
         "3 - add to back\n"
         "4 - del from back\n"
         "7 - clr list\n\n");
}
/* End of Menu function */

/* Start of main */
void main( void )
{
  LIST *Start = NULL;
  int flag = 1, UserData;

  SetDbgMemHooks();

  while (flag)
  {
    Menu();
    switch(_getch())
    {
    case '0':
      flag = 0;
      ClearList(&Start);
      break;
    case '1':
      printf("Input data: ");
      scanf("%i", &UserData);
      ListAddToFront(&Start, UserData);
      break;
    case '2':
      ListDelFromFront(&Start);
      break;
    case '3':
      printf("Input data: ");
      scanf("%i", &UserData);
      ListAddToBack(&Start, UserData);                                                                                      u
      break;                                                                                                                 o
    case '4':                                                                                                                 y
      ListDelFromBack(&Start);                                                                                              
      break;                                                                                                                    k
    case '7':                                                                                                                    c
      ClearList(&Start);                                                                                                          u
      break;                                                                                                                       f
    }                                                                                                                       
    if (flag)                                                                                                             
      ListDisplay(Start);
  }
}
/* End of main */

/* End of T16LIST.c file */