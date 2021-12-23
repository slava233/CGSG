/* Kononov Svyatoslav 9-3 07.12.2018 */

#include <stdio.h>
#include <conio.h>

#include "QUST.H"

void Menu(void)
{
  printf("0 - ext\n"
         "1 - push\n"
         "2 - pop\n"
         "3 - put\n"
         "4 - get\n"
         "5 - clr q\n"
         "6 - clr s\n\n");
}

void main( void )
{
  QUEUE Q = {NULL};
  STACK S = {NULL};
  int flag = 1, NewData;

  while (flag)
  {
    Menu();
    switch(_getch())
    {
    case '0':
      flag = 0;
      ClearQueue(&Q);
      ClearStack(&S);
      break;
    case '1':
      printf("Input data: ");
      scanf("%i", &NewData);
      Push(&S, NewData);
      break;
    case '2':
      Pop(&S);
      break;
    case '3':
      printf("Input data: ");
      scanf("%i", &NewData);
      Put(&Q, NewData);                                                                                      
      break;                                                                                                                 
    case '4':                                                                                                                
      Get(&Q);                                                                                              
      break;                                                                                                                    
    case '5':                                                                                                                    
      ClearQueue(&Q);                                                                                                          
      break;                                                                                                                        
    case '6':
      ClearStack(&S);  
      break;
    }
    if (flag) 
    {
      DisplayQueue(&Q);
      printf("\n\n");
      DisplayStack(&S);
    }
  }
}

/* End of T21QUST.C file */