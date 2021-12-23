#include <glut.h>
#include <math.h>

#include "line.h"

/* Draw line function */
VOID PutLine( INT X1, INT Y1, INT X2, INT Y2, INT Color )
{
  INT x, y, count, F = 0, tmp, IncrX, IncrE, IncrNE, dx, dy;

  dx = X2 - X1;
  dy = Y2 - Y1;

  if (dy < 0)
    COM_SWAP(X1, X2, tmp), COM_SWAP(Y1, Y2, tmp), dx = -dx, dy = -dy;
  if (dx >= 0)
    IncrX = 1;
  else 
    dx = -dx, IncrX = -1;
  x = X1, y = Y1;
  PutPixel(x, y, Color);
  
  if (dx >= dy)
  {
    F = (dy << 1) - dx;
    IncrNE = (dy - dx) << 1;
    IncrE = dy << 1;
    count = dx;
    while (count-- > 0)
    {
      if (F > 0)
        y++, F += IncrNE;
      else
        F += IncrE;
      x += IncrX;
      PutPixel(x, y, Color);
    }
  }
  else 
  {
    F = (dx << 1) - dy;
    count = dy;
    IncrNE = (dx - dy) << 1;
    IncrE = dx << 1;
    while (count-- > 0)
    {
      if (F > 0)
        x += IncrX, F += IncrNE;
      else
        F += IncrE;
      y++;
      PutPixel(x, y, Color);
    }
  }
} /* End of 'PutLine' function */


/* END OF 'GFX02.C' FILE */


