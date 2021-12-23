#include <glut.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "T12.H"
#define Frame_W 1920
#define Frame_H 1080

static byte Frame[Frame_H][Frame_W][3] = {0};
static int Zoom = 3, IsPause = 0;

extern double Speed;

static double FPS;
double DeltaTime = 0;
int i = 2;

void Timer(void)
{
  long t;
  static long StartTime = -1, FPSTime, FrameCount = 0, PauseTime, OldTime;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;
  if (!IsPause)
  {
    DeltaTime = (t - OldTime) / (double)CLOCKS_PER_SEC;
  }
  else
  {
    DeltaTime = 0;
    PauseTime += t - OldTime;
  }
  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
    FPSTime = t;
  }
  OldTime = t;
  printf("FPS: %10.5f\r", FPS);
}

void PutPixel( int X, int Y, int Color )
{
  if ( X < 0 || Y < 0 || X >= Frame_W || Y >= Frame_H )
    return; 
  Frame[Y][X][0] = Color & 0xFF;
  Frame[Y][X][1] = (Color >> 8) & 0xFF;
  Frame[Y][X][2] = (Color >> 16) & 0xFF;
}

void Clear( void )
{
  int i, j;

  for (i = 0; i < H; i++)
    for (j = 0; j < W; j++)
      PutPixel(j, i, 0xFFFFFF);
}

void Display( void )
{
  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);

  Timer();
  StarsMove();
  if(i % 5 == 0)
    Clear();
  StarsDraw();
  StarsMove();

  glDrawPixels(Frame_W, Frame_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);
  i++;

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard( byte Key, int X, int Y)
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
  if (Key == '+')
    Zoom *= 1.25;
  if (Key == '-')
    Zoom /= 1.25;
  if (Key == 'p')
    IsPause = !IsPause;
  if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    ;
  if (Key == 's')
     Speed /= 0.25;
  if (Key == 'w')
     Speed *= 0.25;
}

int main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("0");

  StarsInit();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
  return 0;
}
