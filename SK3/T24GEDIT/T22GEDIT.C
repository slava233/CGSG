#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <commondf.h>

#define FRAME_H 2160
#define FRAME_W 3840

typedef struct tagLIST LIST;
struct tagLIST
{
  int X, Y;
  LIST *Next;
};

static unsigned char frame[FRAME_H][FRAME_W][3];
double Zoom = 3;
int SaveX, SaveY, k = 15, R = 15;
LIST *FloodStack;
DWORD Color = 0x000000;

void Store( int X, int Y )
{
  LIST *NewElement = malloc(sizeof(LIST));

  if (NewElement == NULL || X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;

  NewElement->X = X;
  NewElement->Y = Y; 
  NewElement->Next = FloodStack;
  FloodStack = NewElement;
}

int Restore( int *X, int *Y )
{
  LIST *Old;

  if (FloodStack == NULL )
    return 0;
  Old = FloodStack;
  FloodStack = FloodStack->Next;
  *X = Old->X;
  *Y = Old->Y;
  free(Old);
  return 1;
} 

void PutPixel( int X, int Y, int Color )
{
  if ( X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H )
    return; 
  frame[Y][X][0] = Color & 0xFF;
  frame[Y][X][1] = (Color >> 8) & 0xFF;
  frame[Y][X][2] = (Color >> 16) & 0xFF;
}

DWORD PixelGet(int X, int Y)
{
  return (frame[Y][X][2] << 16) + (frame[Y][X][1] << 8) + frame[Y][X][0];
}

void PutLine( int x1, int y1, int x2, int y2, int Color )
{
   int dx = x2 - x1, dy = y2 - y1 , x = x1, y = y1, count, f, sx = 1, sy = 1;
   if (dx > FRAME_H || dy > FRAME_W)
   {
     printf("Very long line\n");
     _getch();
     exit(30);
   }
   PutPixel(x, y, Color);
   if (dx < 0)
   {
     dx = -dx;
     sx = -1;
   }
   if (dy < 0)
   {
     dy = -dy;
     sy = -1;                    
   }
  if (dy <= dx)
   { 
     int IncrE = 2 * dy, IncrNE = 2 * (dy - dx);
     f = 2 * dy - dx;
     count = dx;
     while (count-- > 0)
     {
       if (f > 0)
         y += sy, f += IncrNE;
       else
         f += IncrE;
       x += sx;
       PutPixel(x, y, Color);
     }
   }
 else
   {
     f = 2 * dx - dy;
     count = dy;
     while (count-- > 0)
     { 
       int IncrE = 2 * dx, IncrNE = 2 * (dx - dy);
       if (f > 0)                      
         x += sx, f += IncrNE;
       else                      
         f += IncrE;            
       y += sy;                      
       PutPixel(x, y, Color); 
     }
   }
}

void Put4Points(int Xc, int Yc)
{
  PutPixel(Xc, Yc + R, Color);
  PutPixel(Xc, Yc - R, Color);
  PutPixel(Xc - R, Yc, Color);
  PutPixel(Xc + R, Yc, Color);
}

void Put8Points(int Xc, int Yc, int X, int Y)
{
  PutPixel(Xc + X, Yc + Y, Color);
  PutPixel(Xc - X, Yc + Y, Color);
  PutPixel(Xc + X, Yc - Y, Color);
  PutPixel(Xc - X, Yc - Y, Color);
  PutPixel(Xc + Y, Yc + X, Color);
  PutPixel(Xc - Y, Yc + X, Color);
  PutPixel(Xc + Y, Yc - X, Color);
  PutPixel(Xc - Y, Yc - X, Color);
}

void Circle(int X, int Y)
{
  int r = R, x = 0, y = x + r, F = 1 - r, IncrE = 3, IncrSE = 5 - 2 * r, Xc = X , Yc = Y;

  Put4Points(Xc, Yc);
  while (1)
  {
    if (F >= 0)
      y--, F += IncrSE, IncrSE += 4;
    else
      F += IncrE, IncrSE += 2;
    IncrE += 2;
    x++;
    if (x > y)
      break;
    Put8Points(Xc, Yc, x, y);
  }
}

void Rose(int X, int Y)
{
  int x, y;

  y = Y;
  while (y <= Y + k * 5)
    PutLine(X - k * 1, Y + k * 4, X, y++, 0x0000FF);

  y = Y + k * 5;
  while (y <= Y + k * 10)
    PutLine(X + k * 1, Y + k * 6, X, y++, 0x0000FF);

  y = Y;
  while (y <= Y + k * 5)
    PutLine(X + k * 1, Y + k * 4, X, y++, 0xFF0000);

  y = Y + k * 5;
  while (y <= Y + k * 10)
    PutLine(X - k * 1, Y + k * 6, X, y++, 0xFF0000);

  x = X;
  while (x <= X + k * 5)
    PutLine(X + k * 1, Y + k * 6, x++, Y + k * 5, 0xFF0000);

  x = X - k * 5;
  while (x <= X)
    PutLine(X - k * 1, Y + k * 4, x++, Y + k * 5, 0xFF0000);

  x = X;
  while (x <= X + k * 5)
    PutLine(X + k * 1, Y + k * 4, x++, Y + k * 5, 0x0000FF);

  x = X - k * 5;
  while (x <= X)
    PutLine(X - k * 1, Y + k * 6, x++, Y + k * 5, 0x0000FF);
}

void FillFlood( int X, int Y, DWORD Color )
{
  DWORD BackColor = PixelGet(X, Y);

  if (BackColor == Color)
    return;

  Store(X, Y);
  while (Restore(&X, &Y))
    if (X >= 0 && Y >= 0 && X < FRAME_W && Y < FRAME_H && PixelGet(X, Y) == BackColor)
    {
      PutPixel(X, Y, Color);
      Store(X - 1, Y);
      Store(X + 1, Y);
      Store(X, Y + 1);
      Store(X, Y - 1);
    }
}

void Mouse( int Button, int State, int X, int Y )
{
  if (Button == GLUT_LEFT_BUTTON)
    if (State == GLUT_DOWN)
    {
      SaveX = X / Zoom;
      SaveY = Y / Zoom;
      PutPixel(X / Zoom, Y / Zoom, Color);
    }
}

void MouseMotion( int X, int Y )
{
  PutLine(SaveX, SaveY, X / Zoom, Y / Zoom, Color);
  SaveX = X / Zoom;
  SaveY = Y / Zoom;
}

void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
  if (Key == 'f')
    glutFullScreen();
  if (Key == ' ')
    FillFlood(X / Zoom, Y / Zoom, Color);
  if (Key == '=')
    Zoom *= 1.25;
  if (Key == '-')
    Zoom /= 1.25;
  if (Key == 'r')
    Rose(X / Zoom, Y / Zoom);
  if (Key == 'c')
  {
    Circle(X / Zoom, Y / Zoom);
    R += 1;
    Color += 0.00001 * ((Color >> 16) + (Color >> 8) + Color);
  }
  if (Key == '1')
    Color = 0x000000;
  if (Key == '2')
    Color = 0x0000FF;
  if (Key == '3')
    Color = 0x00FF00;
  if (Key == '4')
    Color = 0x00FFFF;
  if (Key == '5')
    Color = 0xFF0000;
  if (Key == '6')
    Color = 0xFF00FF;
  if (Key == '7')
    Color = 0xFFFF00;
  if (Key == '8')
    Color = 0xFFFFFF;
  if (Key == 'w')
  {
    k += 2;
    R += 2;
  }
  if (Key == 's')
  {
    k -= 2;
    R -= 2;
  }
}

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);

  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("0");

  glClearColor(0, 0, 0, 0); 

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMotion);

  glutMainLoop();
}

