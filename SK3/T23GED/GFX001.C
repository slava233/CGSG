/* Vashpanov Alexandr, 09-3, 07.12.2018 */
#include "line.h"

/* Draw pixel function */
VOID PutPixel( INT X, INT Y, INT Color )
{
  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;

  Frame[Y][X][0] = Color & 0xFF;
  Frame[Y][X][1] = (Color >> 8) & 0xFF;
  Frame[Y][X][2] = (Color >> 16) & 0xFF;
} /* End of 'PutPixel' function */

/* Get pixel function */
DWORD PixelGet( INT X, INT Y )
{
  return (Frame[Y][X][2] << 16) + (Frame[Y][X][1] << 8) + Frame[Y][X][0];
} /* End of 'GetPixel' function */

/* END OF 'GFX01.C' FILE */

