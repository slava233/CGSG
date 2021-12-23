#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <commondf.h>

#include <glut.h>

INT IsPause = 0;
DOUBLE SyncTime, DeltaTime, FPS;
DOUBLE LatentTime[3] = {0.2, 0.2, 0.2};
BYTE Lab[MAX][MAX];
BYTE AvaX, AvaY;
ENEMY Enemies[MAX_ENEMIES];
static int NumOfEnemies;

/* Timer response function */

void LoadLab( char *FileName )
{
  FILE *F;
  int X = 0, Y = 0, ch;

  if ((F = fopen(FileName, "r")) != NULL)
  {
    memset(Lab, 0, sizeof (Lab));
    while ((ch = fgetc(F)) != EOF)
    {
      switch (ch)
      {
      case ' ':
        Lab[Y][X] = 0;
        break;
      case '*':
        Lab[Y][X] = 1;
        break;
      case 'e':
        Lab[Y][X] = 0;
        if (NumOfEnemies < MAX_ENEMIES)
          {
            Enemies[NumOfEnemies].X = X;
            Enemies[NumOfEnemies].Y = Y;
            Enemies[NumOfEnemies].DeltaTime = 0;
            NumOfEnemies++;
          }
          break;
      case 'a':
          Lab[Y][X] = 0;
          AvaX = X;
          AvaY = Y;
          break;
      case '\n':
          Y++, X = 0;
          break;
      }
      if (X < MAX)
        X++;
      else
        if (Y < MAX)
          Y++, X = 0;
        else
          break;
    }
  }
} /* End of 'LoadLab' function */

VOID Timer( VOID )
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

/* Obtain [0..1] range random value function */
DOUBLE R0( VOID )
{
  return (DOUBLE)rand() / RAND_MAX;
} /* End of 'R0' function */

/* Draw 3D pixel function */
VOID PutPixel( INT X, INT Y, INT Color )
{
  DOUBLE t = Color == 1 ? 1 : 0.1;

  glColor3d(R0() + 0.30 * sin(8 * SyncTime + X * Y), R0(), R0());
  glPushMatrix();
  glScaled(1, t, 1);
  glTranslated(X + 0.5, 0.5, Y + 0.5);
  glutSolidCube(0.99);
  glPopMatrix();
} /* End of 'PutPixel' function */


/* Redraw window hanlde function */
VOID Display( VOID )
{
  INT x, y;
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Timer();

  srand(30);

  glLoadIdentity();

  glPushMatrix();
  /*glRotated(30 * SyncTime, 0, 0, 1);
  glColor3d(1, 0, 0);
  glTranslated(0, 0, -3);
  glutSolidIcosahedron();*/
  glPopMatrix();

  for (y = 0; y < 5; y++)
    for (x = 0; x < 5; x++)
      PutPixel(x, y, (x + y) & 1);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* Keyboard hanlde function */
VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    exit(0);
  else if (Key == 'p')
    IsPause = !IsPause;
} /* End of 'Keyboard' function */

/* Resize window hanlde function */
VOID Reshape( INT W, INT H )
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
  gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);

} /* End of 'Reshape' function */

/* The main program function */
VOID main( INT ArgC, CHAR *ArgV[] )
{
  FLOAT pos[4] = {1, 30, 15, 1};

  /* Library initialization */
  glutInit(&ArgC, ArgV);
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

/* END OF 'T15LAB2D3_1.C' FILE */
