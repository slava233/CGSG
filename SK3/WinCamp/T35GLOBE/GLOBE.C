/* FILE NAME: GLOBE.C
 * PROGRAMMER: SK3
 * DATE: 06.01.2019
 * PURPOSE: Draw sphere work module
 */

#include <time.h>

#include <math.h>

#include "globe.h"

#define N 30
#define M 30
#define R 5

/* Geometry array */
VEC G[N][M];

/* Vector set function.
 * ARGUMENTS:
 *   - coordinates:
 *       DOUBLE X, Y, Z;
 * RETURN:
 *   (VEC)Vector struct
 */
VEC VecSet( DOUBLE X, DOUBLE Y, DOUBLE Z )
{
  VEC r = {X, Y, Z};

  return r;
} /* End of 'VecSet' function */

/* Vector rotation function.
 * ARGUMENTS:
 *   - vector to rotate:
 *       VEC V;
 *   - angle in degrees:
 *       DOUBLE AngleInDegrees;
 * RETURN:
 *   (VEC) new vector.
 */
VEC VecRotateY( VEC V, DOUBLE AngleInDegrees )
{
  DOUBLE a = D2R(AngleInDegrees), si = sin(a), co = cos(a);
  VEC res;

  res.X = V.Z * si + V.X * co;
  res.Y = V.Y;
  res.Z = V.Z * co - V.X * si;

  return res;
} /* End of 'VecRotateY' function */

/* Vector rotation around X axis function.
 * ARGUMENTS:
 *   - vector to rotate:
 *       VEC V;
 *   - angle in degrees:
 *       DOUBLE AngleInDegrees;
 * RETURN:
 *   (VEC) new vector.
 */
VEC VecRotateX( VEC V, DOUBLE AngleInDegrees )
{
  DOUBLE a = D2R(AngleInDegrees), si = sin(a), co = cos(a);
  VEC res;

  res.X = V.X;
  res.Y = V.Y * co - V.Z * si;
  res.Z = V.Y * si + V.Z * co;

  return res;
} /* End of 'VecRotateX' function */

VEC VecRotateZ( VEC V, DOUBLE AngleInDegrees )
{
  DOUBLE a = D2R(AngleInDegrees), si = sin(a), co = cos(a);
  VEC res;
 
  res.X = V.X * si + V.Y * co;
  res.Y = V.X * co - V.Y * si;
  res.Z = V.Z;

  return res;
} /* End of 'VecRotateZ' function */

/* Coordinate translation init function.
 * Arguments:
 *   - angle in degrees:
 *       DOUBLE Angle;
 * RETURN: None.
 */
VOID GLB_Init( DOUBLE Angle )
{
  INT i, j;
  DOUBLE theta, phi, x, y, z;
  VEC res;

  for (theta = 0, i = 0; i < N; i++, theta += PI / (N - 1))
    for (phi = 0, j = 0; j < M; j++, phi += 2 * PI / (M - 1))
    {
      x = R * sin(theta) * cos(phi);
      y = R * cos(theta);
      z = R * sin(theta) * sin(phi);
      res = VecSet(x, y, z);
      if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)
        G[i][j] = VecRotateX(VecRotateZ(VecRotateY(res, Angle), Angle), Angle);
      else if (GetAsyncKeyState(VK_RCONTROL) & 0x8000)
        G[i][j] = VecRotateZ(res, Angle);
      else
        G[i][j] = VecRotateY(res, Angle);
    }
} /* End of 'GLB_Init' function */

/* Draw sphere funciton.
 * ARGUMENTS:
 *   - DC handle:
 *       HDC hDC;
 *   - size of screen:
 *       INT W, INT H;
 * RETURN: None.
 */
VOID GLB_Draw( HDC hDC, INT W, INT H )
{
  INT i, j;
  DOUBLE Wp = 0.1, Hp = 0.1, ProjDist = 0.1;
  static VEC Gv[N][M];
  static POINT pts[N][M];

  if (W > H)
    Wp *= (DOUBLE)W / H;
  else 
    Hp *= (DOUBLE)H / W;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      VEC V;

      V = G[i][j];
      V.Z -= 30;

      Gv[i][j] = V;
    }

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      DOUBLE Xp, Yp;
      INT Xs, Ys;

      Xp = Gv[i][j].X * ProjDist / -Gv[i][j].Z;
      Yp = Gv[i][j].Y * ProjDist / -Gv[i][j].Z;

      Xs = W / 2 + Xp * W / Wp;
      Ys = H / 2 - Yp * H / Hp;

      pts[i][j].x = Xs;
      pts[i][j].y = Ys;
    }

  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(rand(), rand(), rand()));

#if 0
  for (i = 0; i < N; i++)
    for (j = 0; j < M ; j++)
      Ellipse(hDC, pts[i][j].x - 5, pts[i][j].y - 5, 5 + pts[i][j].x, 5 + pts[i][j].y);  

  for (i = 0; i < N; i++)
  {
    MoveToEx(hDC, pts[i][0].x, pts[i][0].y, 0);
    for (j = 1; j < M; j++)
      LineTo(hDC, pts[i][j].x, pts[i][j].y);
  }

  for (j = 1; j < M; j++)
  {
    MoveToEx(hDC, pts[0][j].x, pts[0][j].y, 0);
    for (i = 0; i < N; i++)
      LineTo(hDC, pts[i][j].x, pts[i][j].y);
  }
#endif /* 0 */

  for (i = 0; i < N - 1; i++)
    for (j = 0; j < M - 1; j++)
    {
      POINT pts1[4];

      pts1[0] = pts[i][j];
      pts1[1] = pts[i][j + 1];
      pts1[2] = pts[i + 1][j + 1];
      pts1[3] = pts[i + 1][j];

      if ((pts1[0].x - pts1[1].x) * (pts1[0].y + pts1[1].y) + 
          (pts1[1].x - pts1[2].x) * (pts1[1].y + pts1[2].y) +
          (pts1[2].x - pts1[3].x) * (pts1[2].y + pts1[3].y) +
          (pts1[3].x - pts1[0].x) * (pts1[3].y + pts1[0].y) < 0)
        Polygon(hDC, pts1, 4);
    }
} /* End of 'GLB_Draw' function */

/* END OF 'GLOBE.C' FILE */
