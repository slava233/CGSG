#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "life.h"

static byte frame[FRAME_H][FRAME_W][3];
double Zoom = 3;

void Keyboard( byte Key, int X, int Y)
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
  if (Key == '=')
    Zoom *= 1.25;
  if (Key == '-')
    Zoom /= 1.25;
  if (Key == ' ')
  {
    int n = 0;
    while (n < 300)
      PutPixel(rand() % 800, rand() % 600, 0x00FF00), n++;
  }
}

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  LifeStep();

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);

  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void PutPixel( int X, int Y, int Color )
{
  if ( X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H )
    return; 
  frame[Y][X][0] = Color & 0xFF;
  frame[Y][X][1] = (Color >> 8) & 0xFF;
  frame[Y][X][2] = (Color >> 16) & 0xFF;

}

void main( int argc, char *argv[] )
{
  LifeInit();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("0");

  glClearColor(0, 0, 0, 0); 

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
}



