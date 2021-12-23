/* FILE NAME: MTH.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: MATH LIBRARY
 */

#ifndef __MTH_H_
#define __MTH_H_

#include <math.h>
#include <commondf.h>

#define PI 3.14159265358979323846
#define D2R(X) ((X) * PI / 180)
#define Degree2Radian(a) D2R(a)
#define P_MATH 0.000001

/* Base types of float */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Type for vector in space */
typedef struct tagVEC
{
  FLT X, Y, Z; /* Vector coordinates */
} VEC;

/* Type for vector in space */
typedef struct tagVEC2
{
  FLT X, Y; /* Vector coordinates */
} VEC2;

/* Type for vector in space */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Vector coordinates */
} VEC4;

/* Type for Matrix - array in struct */
typedef struct tagMATRIX
{
  FLT M[4][4];
} MATR;

/* Set vector coordinates function.
 * ARGUMENTS:
 *  - Vector coordinates:
 *      FLT X, Y, Z;
 * RETURNS:
 *  (VEC) Vector.
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;

  return v;
} /* End of 'VecSet' function */

/* Set vector coordinates function.
 * ARGUMENTS:
 *  - Vector coordinates:
 *      FLT X, Y;
 * RETURNS:
 *  (VEC) 2D-Vector.
 */
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v;

  v.X = X;
  v.Y = Y;

  return v;
} /* End of 'Vec2Set' function */

/* Set vector coordinates function.
 * ARGUMENTS:
 *  - Vector coordinates:
 *      FLT X, Y;
 * RETURNS:
 *  (VEC) Vector with additional coordinate.
 */
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  v.W = W;

  return v;
} /* End of 'Vec4Set' function */

/* Vec add vec function.
 * ARGUMENTS:
 *  - Vectors in symm:
 *      VEC v1, v2;
 * RETURNS:
 *  (VEC) Vector symm.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Vec sub vec function.
 * ARGUMENTS:
 *  - Vectors in symm:
 *      VEC v1, v2;
 * RETURNS:
 *  (VEC) Vector symm.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vec mul num function.
 * ARGUMENTS:
 *  - Vector:
 *      VEC V1;
 *  - Number:
 *      FLT N;
 * RETURNS:
 *  (VEC) New vector.
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Vec divide by num function.
 * ARGUMENTS:
 *  - Vector:
 *      VEC V1;
 *  - Number:
 *      FLT N;
 * RETURNS:
 *  (VEC) New vector.
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  if (N == 0)
    return VecSet(0, 0, 0);
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */


/* Inverse vector function.
 * ARGUMENTS:
 *  - Vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) Inverse vector.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */


/* Dot product vectors in 2D space function.
 * ARGUMENTS:
 *  - Vectors:
 *      VEC V1, V2;
 * RETURNS:
 *  (FLT) Product.
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */


/* Cross product vectors in 3D space function.
 * ARGUMENTS:
 *  - Vectors:
 *      VEC V1, V2;
 * RETURNS:
 *  (VEC) New vector-product.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, 
                V1.Z * V2.X - V1.X * V2.Z, 
                V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Take square of vector len function.
 * ARGUMENTS:
 *  - Vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) Square of vectors len.
 */
__inline FLT VecLen2( VEC V )
{
  return COM_SQR(V.X) + COM_SQR(V.Y) + COM_SQR(V.Z);
} /* End of 'VecLen2' function */

/* Take vector len function.
 * ARGUMENTS:
 *  - Vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) Vectors len.
 */
__inline FLT VecLen( VEC V )
{
  return sqrt(VecLen2(V));
} /* End of 'VecLen' function */

/* Normalise vector
 * ARGUMENTS:
 *  - Vector:
 *      VEC V;
 * RETURNS:
 *  (VEC) Normalised vector.
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecLen(V);

  if (len == 0)
    return V;
  else
    return VecSet(V.X / len, V.Y / len, V.Z / len);
} /* End of 'VecNormalize' function */

/* Transpose matrix function.
 * ARGUMENTS:
 *  - Matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) Transposed matrix.
 */
_inline MATR MatrTranspose( MATR M )
{
  MATR R =
  {
    {
      {M.M[0][0], M.M[1][0], M.M[2][0], M.M[3][0]},
      {M.M[0][1], M.M[1][1], M.M[2][1], M.M[3][1]},
      {M.M[0][2], M.M[1][2], M.M[2][2], M.M[3][2]},
      {M.M[0][3], M.M[1][3], M.M[2][3], M.M[3][3]}
    }
  };

  return R;
} /* End of 'MatrTranspose' function */

/* Transform vector by matrix-transformation
 * with no-afin transformation function.
 * ARGUMENTS:
 *  - Vector need to transform:
 *      VEC V;
 *  - Matrix transformation:
 *      MATR M;
 * RETURNS:
 *  (VEC) Transformed vector.
 */
__inline VEC VecMulMatr4x4( VEC V, MATR M )
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w,
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Transform vector by matrix-transformation function.
 * ARGUMENTS:
 *  - Vector need to transform:
 *      VEC V;
 *  - Matrix transformation:
 *      MATR M;
 * RETURNS:
 *  (VEC) Transformed vector.
 */
_inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0], 
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1],
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2]);
} /* End of 'VectorTransform' function */

/* Transform point by matrix-transformation function.
 * ARGUMENTS:
 *  - Point need to transform:
 *      VEC V;
 *  - Matrix transformation:
 *      MATR M;
 * RETURNS:
 *  (VEC) Transformed point.
 */
_inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0],
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1],
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]);
} /* End of 'PointTransform' function */

/* Identity of matrixes product */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Matrix identity function.
 * ARGUMENTS: None;
 * RETURNS:
 *  (MATR) Matrix-identity.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Set matrix-translate function.
 * ARGUMENTS:
 *  - Vector-translate:
 *      VEC V;
 * RETURNS:
 *  (MATR) Matrix-translate.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
} /* End of 'MatrTranslate' function */

/* Set matrix-rotateX function.
 * ARGUMENTS:
 *  - Angle rotate:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) Matrix-rotateX.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR m = UnitMatrix;

  m.M[1][1] = co;
  m.M[1][2] = si;
  m.M[2][1] = -si;
  m.M[2][2] = co;

  return m;
} /* End of 'MatrRotateX' function */

/* Set matrix-rotateY function.
 * ARGUMENTS:
 *  - Angle rotate:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) Matrix-rotateY.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR m = UnitMatrix;

  m.M[0][0] = co;
  m.M[0][2] = -si;
  m.M[2][0] = si;
  m.M[2][2] = co;

  return m;
} /* End of 'MatrRotateY' function */

/* Set matrix-rotateZ function.
 * ARGUMENTS:
 *  - Angle rotate:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) Matrix-rotateZ.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR m = UnitMatrix;

  m.M[0][0] = co;
  m.M[0][1] = si;
  m.M[1][0] = -si;
  m.M[1][1] = co;

  return m;
} /* End of 'MatrRotateZ' function */

/* Set matrix-scaling function.
 * ARGUMENTS:
 *  - Vector-scaling:
 *      VEC V;
 * RETURNS:
 *  (MATR) Matrix-scaling.
 */
__inline MATR MatrScale( VEC S )
{
  MATR m = UnitMatrix;

  m.M[0][0] = S.X;
  m.M[1][1] = S.Y;
  m.M[2][2] = S.Z;

  return m;
} /* End of 'MatrScale' function */


/* Set matrix-rotate function.
 * ARGUMENTS:
 *  - Vector by rotating:
 *      VEC V;
 *  - Angle rotate:
 *      FLT AngleInDegree;
 * RETURNS:
 *  (MATR) Matrix-rotate.
 */
__inline MATR MatrRotate( FLT AngleToDegree,
                 VEC R )
{
  FLT A = D2R(AngleToDegree), si = (sin(A) < P_MATH ? 0 : sin(A)), co = (cos(A) < P_MATH ? 0 : cos(A));
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co),
         V.X * V.Y * (1 - co) + V.Z * si,
           V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si,
         co + V.Y * V.Y * (1 - co),
           V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si,
         V.Z * V.Y * (1 - co) - V.X * si,
           co + V.Z * V.Z * (1 - co),       0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotate' function */

/* Make matrix product function.
 * ARGUMENTS:
 *  - Matrixis:
 *      MATR M1, M2;
 * RETURNS:
 *  (MATR) Matrix-product.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  int i, j, k;
  MATR r = UnitMatrix;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
} /* End of 'MatrMulMatr' function */

/* Count matrix 3x3 determinate function.
 * ARGUMENTS:
 *  - Matrix elements:
 *      MATR A11, A12, A13
 *           A21, A22, A23
 *           A31, A32, A33;
 * RETURNS:
 *  (MATR) Matrix determinate.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                            FLT A21, FLT A22, FLT A23,
                            FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Count matrix 4x4 determinate function.
 * ARGUMENTS:
 *  - Matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) Matrix determinate.
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) - 
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                              M.M[2][0], M.M[2][2], M.M[2][3],
                              M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                              M.M[2][0], M.M[2][1], M.M[2][2],
                              M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Male inverse matrix function.
 * ARGUMENTS:
 *  - Matrix:
 *      MATR M;
 * RETURNS:
 *  (MATR) Inverse matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  FLT det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

  /* build adjoint matrix */
  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[2][0], M.M[2][2], M.M[2][3],
                  M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[2][0], M.M[2][1], M.M[2][2],
                  M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                 M.M[1][1], M.M[1][2], M.M[1][3],
                 M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]);
  r.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[1][0], M.M[1][2], M.M[1][3],
                  M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[1][0], M.M[1][1], M.M[1][2],
                  M.M[2][0], M.M[2][1], M.M[2][2]);

  r.M[0][0] /= det;
  r.M[1][0] /= det;
  r.M[2][0] /= det;
  r.M[3][0] /= det;
  r.M[0][1] /= det;
  r.M[1][1] /= det;
  r.M[2][1] /= det;
  r.M[3][1] /= det;
  r.M[0][2] /= det;
  r.M[1][2] /= det;
  r.M[2][2] /= det;
  r.M[3][2] /= det;
  r.M[0][3] /= det;
  r.M[1][3] /= det;
  r.M[2][3] /= det;
  r.M[3][3] /= det;

  return r;
} /* End of 'MatrInverse' function */

/* Make Matrix of View function.
 * ARGUMENTS:
 *  - viewrs position:
 *      VEC Loc;
 *  - where viewers looks:
 *      VEC At;
 *  - exemplary direction up:
 *      VEC Up1;
 * RETURNS:
 *  (MATR) Matrix of View.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m = 
  {
    {
      {Right.X,                Up.X,                -Dir.X,              0},
      {Right.Y,                Up.Y,                -Dir.Y,              0},
      {Right.Z,                Up.Z,                -Dir.Z,              0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

/* Make frustrum matrix function.
 * ARGUMENTS:
 *  - properties of frame:
 *      FLT l (left point),
 *          r (right point),
 *          b (bottom point),
 *          t (top point),
 *          n (nearest point),
 *          f (fair point);
 * RETURNS:
 *  (MATR) Frustrum matrix.
 */
__inline MATR FrustumMatr( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  MATR M =
  {
    {
      {2 * n / (r - l),    0,                 0,                    0},
      {0,                  2 * n / (t - b),   0,                    0},
      {(r + l) / (r - l),  (t + b) / (t - b), -(f + n) / (f - n),  -1},
      {0,                  0,                 -2 * n * f / (f - n), 0},
    }
  };

  return M;
} /* End of 'MatrFrusrtum' function */

#endif /* __MTH_H_ */

/* END OF 'MTH.H' FILE */
