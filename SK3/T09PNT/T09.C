#include <stdlib.h>
#include <glut.h>

#define FRAME_W 600
#define FRAME_H 300

float Frame[FRAME_H][FRAME_W][3];

void Display( void )
{
  float n;

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  n = 1;
  while (n-- > 0)
    Frame[rand() % FRAME_H][rand() % FRAME_W][rand() % 3] = rand() / (double)RAND_MAX;

  glPixelZoom(3, 3);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_FLOAT, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard( unsigned char Key, int X, int Y)
{
  if (Key == 27)
    exit(0);
  else if (Key == 'f')
    glutFullScreen();
  else if (Key == 'a')
  {
    X /= 3;
    Y /= 3;
    if (X >= 0 && Y >= 0 && X < FRAME_W && Y < FRAME_H)
    {
      Frame[Y][X][0] = 255;
      Frame[Y][X][1] = 255;
      Frame[Y][X][2] = 255;
    }
  }
}

int main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("0");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
  return 0;
}