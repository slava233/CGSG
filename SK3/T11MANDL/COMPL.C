#include <math.h>

#include "compl.h"

#define X1 2
#define X0 -2
#define Y1 2
#define Y0 -2
#define W 300
#define H 250
#define RGB(r, g, b) \
  ((((byte)(r)) << 16) | (((byte)(g)) << 8) | ((byte)(b)))

COMPL ComplSet( DBL A, DBL B )
{
  COMPL Z;

  Z.Re = A * (X1 - X0) / W + X0;
  Z.Im = B * (Y1 - Y0) / H + Y0;

  return Z;
}

COMPL ComplAddCompl( COMPL A, COMPL B )
{
  COMPL Z;

  Z.Re = A.Re + B.Re;
  Z.Im = A.Im + B.Im;

  return Z;
}

COMPL ComplMultCompl( COMPL A, COMPL B )
{
  COMPL Z;

  Z.Re = (A.Re * B.Re) - (A.Im * B.Im);
  Z.Im = (A.Re * B.Im) + (B.Re * A.Im);

  return Z;
}

DBL ComplNorm2( COMPL Z )
{
  return (Z.Re * Z.Re) + (Z.Im * Z.Im);
}

void PutMandl( void )
{
  int n, xs, ys;
  COMPL Z, C = ComplSet((sqrt(3) / 2) * 120 + 50 * sin(SyncTime + 3), (sqrt(3) / 2) * 180 + 50 * sin(1.5 * SyncTime));

  for (ys = 0; ys < H; ys++)
    for (xs = 0; xs < W; xs++)
    {
      Z = ComplSet(xs, ys);
      n = Julia(Z, C);
      PutPixel(xs, ys, RGB(n * 15, n * 30, n * 24));
    }
}

int Mandelbrot( COMPL Z )
{
  COMPL Z0 = Z;
  int n = 1;

  while (n++ < 255 && ComplNorm2(Z0) < 4)
  {
    Z0 = ComplMultCompl(Z0, Z0);
    Z0 = ComplAddCompl(Z0, ComplSet(0.35, 0.39));
  }
  return n;
}

int Julia( COMPL Z, COMPL C )
{
  COMPL Z0 = Z;
  int n = 1;

  while (n++ < 255 && ComplNorm2(Z0) < 4)
  {
    Z0 = ComplMultCompl(Z0, Z0);
    Z0 = ComplAddCompl(Z0, C);
  }
  return n;
}