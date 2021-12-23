#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glut.h>

#include "compl.h"

#define FRAME_H 1080
#define FRAME_W 1920

static byte Frame[FRAME_H][FRAME_W];

static double Zoom = 3;

DBL FPS, SyncTime;

void Timer( void )
{
  long t;
  static long StartTime = -1, FPSTime, FrameCount;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;

  SyncTime = (t - StartTime) / (DBL)CLOCKS_PER_SEC;
  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DBL)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
}

/* Putting pixel by x y */
void PutPixel( int X, int Y, int Color )
{
  /* X /= Zoom;
   * Y /= Zoom; */

  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;

  Frame[Y][X] = Color & 0xFF;
} /* End of 'PutPixel' function */

/* Display function */
void Display( void )
{ 
  Timer(); 

  glClear(GL_COLOR_BUFFER_BIT);

  PutMandl();

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);     
  glDrawPixels(FRAME_W, FRAME_H, GL_BLUE, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* Keyboard function */
void Keyboard( byte Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
  else if (Key == 'a')
    PutPixel(X, Y, 1000);
  else if (Key == '=')
    Zoom *= 1.25;
  else if (Key == '-')
    Zoom /= 1.25;
  else if (Key == 'f')
    glutFullScreen();
} /* End of 'Keyboard' function */

/* MAIN */
void main( int argc, char *argv[] )
{
  /* GLUT library init */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  /* Create work window */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Phys-Math Lyceum # 30 forever!!!");
  
  glClearColor(0.3, 0.5, 0.7, 1);
  
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
} /* End of MAIN */