/* Vashpanov Alexandr, 09-3, 07.12.2018 */
#include <glut.h>
#include <math.h>

#include "line.h"

static INT Cx, Cy;

/* Draw four point function */
VOID Put4Pixel( INT X, INT Y, INT R, INT Color)
{
  PutPixel(Cx, Cy + R, Color);
  PutPixel(Cx, Cy - R, Color);
  PutPixel(Cx + R, Cy, Color);
  PutPixel(Cx - R, Cy, Color);
} /* End of 'Put4Pixel' function */

/* Draw eight point function */
VOID Put8Pixel( INT X, INT Y, INT R, INT Color)
{
  PutPixel(Cx + X, Cy + Y, Color);
  PutPixel(Cx - X, Cy + Y, Color);
  PutPixel(Cx + X, Cy - Y, Color);
  PutPixel(Cx - X, Cy - Y, Color);
  PutPixel(Cx + X, Cy + Y, Color);
  PutPixel(Cx - X, Cy + Y, Color);
  PutPixel(Cx + X, Cy - Y, Color);
  PutPixel(Cx - X, Cy - Y, Color);
} /* End of 'Put8Pixel' function */

/* Draw circle function */
VOID PutCircle( INT X1, INT Y1, INT R )
{
  INT x, y, F = 0, DeltaE, DeltaSE;

  Cx = X1;
  Cy = Y1;

  F = 1 - R;

  x = 0, y = R;
  DeltaE = 3; 
  DeltaSE = 5 - 2 * 3;
  Put4Pixel(x, y, R, COLOR);

  while (x <= y)
  {
    if (F >= 0)
      y--, F += DeltaSE, DeltaSE += 4;
    else
      F += DeltaE, DeltaSE += 2;
    DeltaE += 2;
    x++;
    if (x > y)
      break;
    if (x != y)
      Put8Pixel(x, y, R, COLOR);
  }
} /* End of 'PutCircle' function */


/* END OF 'GFX03.C' FILE */


