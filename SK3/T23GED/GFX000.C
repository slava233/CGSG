/* Vashpanov Alexandr, 09-3, 24.12.2018 */  
#include <glut.h>

#include "line.h"

BYTE Frame[FRAME_H][FRAME_W][3];
static BYTE Mark[FRAME_H][FRAME_W];

VOID DrawFrame( VOID )
{
  glPixelZoom(Zoom, -Zoom);
  glRasterPos2d(-1, 1);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
}

VOID FlashFrame( VOID )
{
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}
