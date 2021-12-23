/* Vashpanov Alexandr, 09-3, 24.12.2018 */

#include <glut.h>
#include <math.h>

#include "line.h"

LIST *FloodStack;

/* Push in stack function */
VOID Store( INT X, INT Y )
{
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    return;

  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;

  NewElement->X = X;
  NewElement->Y = Y; 
  NewElement->Next = FloodStack;
  FloodStack = NewElement;
} /* End of 'Store' function */

/* Pop from stack function */
INT Restore( INT *X, INT *Y )
{
  LIST *Old;

  if (FloodStack == NULL )
    return 0;
  Old = FloodStack;
  FloodStack = FloodStack->Next;
  *X = Old->X;
  *Y = Old->Y;
  free(Old);
  return 1;
} /* End of 'Restore' function */

VOID FillFlood( INT X, INT Y, DWORD Color )
{
  DWORD BackColor = PixelGet(X, Y);

  if (BackColor == Color)
    return;
  Store(X, Y);
  while (Restore(&X, &Y))
    if (X >= 0 && Y >= 0 && X < W && Y < H && PixelGet(X, Y) == BackColor)
    {
      PutPixel(X, Y, Color);
      Store(X - 1, Y);
     
      Store(X + 1, Y);
    
      Store(X, Y + 1);
      
      Store(X, Y - 1);
    }
}

/* Push in stack function */
VOID StoreL( INT L, INT R, INT Y )
{
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL)
    return;

  if (Y < 0 || Y >= FRAME_H)
    return;

  NewElement->L = L;
  NewElement->R = R;
  NewElement->Y = Y;
  NewElement->Next = FloodStack;
  FloodStack = NewElement;
} /* End of 'Store' function */

/* Pop from stack function */
INT RestoreL( INT *L, INT *R, INT *Y )
{
  LIST *Old;

  if (FloodStack == NULL )
    return 0;
  Old = FloodStack;
  FloodStack = FloodStack->Next;
  *L = Old->L;
  *R = Old->R;
  *Y = Old->Y;
  free(Old);
  return 1;
} /* End of 'Restore' function */

/*VOID FillFlood2( INT X, INT Y, DWORD Color )
{
  INT L = X, R = Y, x, left, Y1 = Y;
  DWORD BackColor = PixelGet(X, Y);

  if (BackColor == Color)
    return;
  StoreL(X, X, Y);
  Y1 = Y;
  while (RestoreL(&L, &R, &Y))
  {
    L--;
    while (L >= 0 && PixelGet(L, Y) == BackColor)
      L--;
    L++;

    R++;
    while (R < FRAME_W && PixelGet(R, Y) == BackColor)
      R++;
    R--;

    for (x = L; x < R; x++)
      PutPixel(x, Y, COLOR);

    Y--;
    x = L;
    while (x <= R)
    {
     
      while (x <= R && PixelGet(x, Y) != BackColor)
        x++;
      if (x <= R)
      {
      
        left = x;
        while (x <= R && PixelGet(x, Y) == BackColor)
          x++;
        StoreL(left, x - 1, Y);
      }
    }
    Y += 2;
    DrawFrame();
     Look for lower line 
     Y1--;
    while (RestoreL(&L, &R, &Y1))
    {
      
      Y1++;
      x = L;
      while (x <= R)  
      {
        
        while (x <= R && PixelGet(x, Y1) != BackColor)
          x++;
        if (x <= R)
        {
          
          left = x;
          while (x <= R && PixelGet(x, Y1) == BackColor)
            x++;
          StoreL(left, x - 1, Y1);
        }
      }
      Y1 += 2;
     
    }
  }
}
}*/

/* END OF 'GFX04.C' FILE */

