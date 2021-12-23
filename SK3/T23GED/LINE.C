/* Vashpanov Alexandr, 09-3, 24.12.2018 */
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include "line.h"
#define Color 0xFFFFFF

//#define F(x, y) (dy * x - dx * y - (dy * X1 - dx * Y1))
INT SaveX, SaveY;

/* glut Mouse function */
/*VOID Mouse( INT Button, INT State, INT X, INT Y )
{
  if (Button == GLUT_LEFT_BUTTON)
  {
    if (State == GLUT_DOWN)
    {
      SaveX = X / Zoom, SaveY = Y / Zoom;
      PutPixel(X / Zoom, Y / Zoom, 0xFFFFFF);
    }
  }
}*/ /* End of 'Mouse' function */

/*VOID MouseMotion( INT X, INT Y )
{
  Rose( X / Zoom, Y / Zoom, 5 , 1 , 0x0F0FFF, 0xF00A0F);
  SaveX = X / Zoom, SaveY = Y / Zoom;
}*//* End of 'Mouse' function */

/*VOID Rose( INT x, INT y, INT L, INT H, INT Color1, INT Color2)
{
  INT i;
  for (i = 0; i < L; i++)
    {
      //
      PutLine(x + H, y + H, x, y + i, Color2);
      PutLine(x - H, y + H, x, y + i, Color1);
      //
      PutLine(x + H, y - H, x, y - i, Color1);
      PutLine(x - H, y - H, x, y - i, Color2);
      //
      PutLine(x + H, y + H, x + i, y, Color1);
      PutLine(x + H, y - H, x + i, y, Color2);
      //
      PutLine(x - H, y + H, x - i, y, Color2);
      PutLine(x - H, y - H, x - i, y, Color1);
    }
}*/

static INT Cx, Cy;

