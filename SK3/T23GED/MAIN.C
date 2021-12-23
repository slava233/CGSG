/* Vashpanov Alexandr, 09-3, 2  4.12.2018 */
#include <glut.h>
#include <stdlib.h>

#include "line.h"

BYTE Frame[FRAME_H][FRAME_W][3];
INT SaveX, SaveY;
DOUBLE Zoom = 1.0;

/* glut Display function */
VOID Display( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);  
  PutCircle( 150, 150, 40 );   
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* glut Keyboard function */
VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
  else if (Key == '+' || Key == '=')
    Zoom *= 1.25;
  else if (Key == '-')
    Zoom /= 1.25;
  else if (Key == 'e')
    FillFlood(X, Y, 0xFF0000);
  /*else if (Key == 'f')
    FillFlood2(X, Y, 0xFF0000);*/
} /* End of 'Keyboard' function */
INT SaveX, SaveY;

/* glut Mouse function */
VOID Mouse( INT Button, INT State, INT X, INT Y )
{
  if (Button == GLUT_LEFT_BUTTON)
  {
    if (State == GLUT_DOWN)
    {
      SaveX = X / Zoom, SaveY = Y / Zoom;
      PutPixel(X / Zoom, Y / Zoom, 0xFFFFFF);
    }
  }
} /* End of 'Mouse' function */

VOID MouseMotion( INT X, INT Y )
{
  PutLine( SaveX / Zoom, SaveY / Zoom, X / Zoom , Y / Zoom , 0x0F0FFF);
  SaveX = X / Zoom, SaveY = Y / Zoom;
}/* End of 'Mouse' function */

/* The main function */
VOID main( INT argc, CHAR *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("Graphic Editor");
  glutFullScreen();

  glutDisplayFunc(Display);

  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMotion);
  glutMainLoop();
} /* End of 'main' function */


/* END OF 'T24GEDIT.C' FILE */

