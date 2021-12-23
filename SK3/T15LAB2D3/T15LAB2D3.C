#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <commondf.h>
#include <glut.h>

#include "headers.h"

#define FRAME_W 300
#define FRAME_H 200

static BYTE Frame[FRAME_H][FRAME_W][3];
static int Zoom = 3, IsPause = 0;
int GAME_OVER = 0;
DOUBLE SyncTime, DeltaTime, FPS;

/* Obtain [0..1] range random value function */
DOUBLE R0( VOID )
{
  return (DOUBLE)rand() / RAND_MAX;
} /* End of 'R0' function */

/* The Timer function */
void Timer( void )
{
  LONG t;
  static LONG StartTime = -1, FPSTime, FrameCount, PauseTime, OldTime;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = OldTime = t;

  if (!IsPause)
  {
    DeltaTime = (t - OldTime) / (DOUBLE)CLOCKS_PER_SEC;
    SyncTime = (t - StartTime - PauseTime) / (DOUBLE)CLOCKS_PER_SEC;
  }
  else
  {
    DeltaTime = 0;
    PauseTime += t - OldTime;
  }

  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DOUBLE)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
    /* printf("FPS: %10.5f\r", FPS); */
  }
  OldTime = t;
} /* End of 'Timer' function */

/* Draw 3D pixel function */
VOID PutPixel( INT X, INT Y, INT Color )
{
  DOUBLE t = Color != 0 ? 1 : 0.1;
  if (Color == 0xFF0000)
    glColor3d(/*R0() + 0.30 * sin(8 * SyncTime + X * Y), R0(), R0()*/1, 0, 0);
  if (Color == 0x00FF00)
    glColor3d(/*R0() + 0.30 * sin(8 * SyncTime + X * Y), R0(), R0()*/0, 1, 0);
  if (Color == 0x0000FF)
    glColor3d(/*R0() + 0.30 * sin(8 * SyncTime + X * Y), R0(), R0()*/0, 0, 1);

  glPushMatrix();
  glScaled(1, t, 1);
  glTranslated(X + 0.5, 0.5, Y + 0.5);
  glutSolidCube(0.99);
  glPopMatrix();
} /* End of 'PutPixel' function */

/* Redraw window hanlde function */
void Display( void )
{   
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Timer();

  srand(30);

  glLoadIdentity();

  LabLoad("Z:\\SK3\\T15LAB2D3\\LAB.TXT");
  DrawPlace();

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* The work-with-keyboard function */
void Keyboard( unsigned char Key, int X, int Y )
{
  switch (Key)
  {
  case 'w':
    if (AvaY > 0 && Lab[AvaY - 1][AvaX] == 0)
      AvaY--;
    break;
  case 'a':
    if (AvaX > 0 && Lab[AvaY][AvaX - 1] == 0)
      AvaX--;
    break;
  case 's':
    if (Lab[AvaY + 1][AvaX] == 0)
      AvaY++;
    break;
  case 'd':
    if (Lab[AvaY][AvaX + 1] == 0)
      AvaX++;
    break;
  case 'f':
    glutFullScreen();
    break;
  case 'p':
    IsPause = !IsPause;
    break;                                    
  case '=':
    Zoom *= 2;
    break;
  case '-':
    Zoom /= 2;
    break;
  case 27:
    exit(0);
  }
} /* End of 'Keyboard' function */

/* Resize window hanlde function */
void Reshape( int W, int H )
{
  DOUBLE s = 0.1, rx = s, ry = s;

  if (W >= H)
    rx *= (DOUBLE)W / H;
  else
    ry *= (DOUBLE)H / W;

  glViewport(0, 0, W, H);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-rx, rx, -ry, ry, s, 1000);
  gluLookAt(20, 50, 30, 0, 0, 0, 0, 1, 0);                      
  glMatrixMode(GL_MODELVIEW);

} /* End of 'Reshape' function */

/* Tme main program functon */
void main( int argc, char *argv[] )
{
  FLOAT pos[4] = {1, 30, 15, 1};

  /* Library initialization */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  /* Window creation */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 800);
  glutCreateWindow("CGSG'Lab3D");

  /* Callbacks setup */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);

  /* OpenGL setup */
  glClearColor(0.3, 0.7, 0.5, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  /* Go to main loop */
  glutMainLoop();
} /* End of 'main' function */

/* END OF 'T15LAB2D3.C' FILE*/
