#include <stdlib.h>

#include "T12.H"

#define Size 1
#define INFINITY 100000
#define COUNT_OF_STARS 50000
#define ProjDist 1.0

static VEC Stars[COUNT_OF_STARS];

double Speed = 10000;
static Wp, Hp;

double R0(void)
{
  return rand() / (double)RAND_MAX;
}

double R1(void)
{
  return 2.0 * rand() / (double)RAND_MAX - 1;
}

void ProjSetup(void)
{
  if (W >= H)
  {
    Wp = Size * W / H;
    Hp = Size;
  }
  else
  {
    Wp = Size;
    Hp = Size * H / W;
  }
}

void StarsInit(void)
{
  int i;

  for (i = 0; i < COUNT_OF_STARS; i++)
  {
    Stars[i].X = INFINITY * R1();
    Stars[i].Y = INFINITY * R1();
    Stars[i].Z = INFINITY * R0();
  }
  ProjSetup();
}

void StarsMove(void)
{
  int i;

  for(i = 0; i < COUNT_OF_STARS; i++)
  {
    if (Stars[i].Z < 0)
    {
      Stars[i].Z = INFINITY;
      continue;
    }
    Stars[i].Z -= Speed * DeltaTime;
  } 
}

void StarsDraw(void)
{
  int i, xs, ys;
  double xp, yp;

  for (i = 0; i < COUNT_OF_STARS; i++)
  {
    xp = Stars[i].X * ProjDist / Stars[i].Z;
    yp = Stars[i].Y * ProjDist / Stars[i].Z;
    xs = (int)(W / Wp * xp + W / 2);
    ys = (int)((-yp) * H / Hp + H / 2);
    
    PutPixel(xs, ys, 0x0);
  }
}