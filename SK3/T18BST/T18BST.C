/* Kononov Svyat 9-3 19.11.2018 */

#include <stdio.h>

#include "BST.H"

/* Start of Menu function */
void Menu(void)
{
  printf("0 - ext\n"
         "1 - acs rec\n"
         "2 - acs no rec\n"
         "3 - drw tree\n"
         "4 - clr tree\n\n");
}
/* End of Menu function */

/* Start of main */
void main( void )
{
  TREE *Root = NULL;
  int flag = 1, Key;

  SetDbgMemHooks();

  while (flag)
  {
    Menu();
    switch(_getch())
    {
    case '0':
      ClearTree(&Root);
      flag = 0;
      break;
    case '1':
      printf("\nPress key: \n");
      scanf("%i", &Key);
      AccessRecTree(&Root, Key);
      break;
    case '2':
      printf("\nPress key: \n");
      scanf("%i", &Key);
      AccessNonRecTree(&Root, Key);
      break; 
    case '3':
      DrawTree(&Root, 0);
      break;
    case '4':
      ClearTree(&Root);
      break;
    }                                                                   
  }
}
/* End of main */
