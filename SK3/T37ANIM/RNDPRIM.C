/* FILE NAME: RNDPRIM.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Primitive rendering
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"

/* Create empte primitive function.
 * ARGUMENTS:
 *  - point to new primitive:
 *      SK3PRIM *Pr;
 *  - point to new vertex:
 *      SK3VERTEX *V;
 *  - count of vertex:
 *      INT NumOfV;
 *  - array of indexes:
 *      INT *Ind;
 *  - count of indexes:
 *      INT NumOfI;
 * RETURNS:
 *   (BOOL) creation primitive result.
 */
static BOOL SK3_RndPrimCreate( SK3PRIM *Pr, SK3VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  memset(Pr, 0, sizeof(SK3PRIM));

  glGenBuffers(1, &Pr->VBuf);
  glGenVertexArrays(1, &Pr->VA);

  /* Vertexes */
  glBindVertexArray(Pr->VA);

  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(SK3VERTEX) * NumOfV, V, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(SK3VERTEX), (VOID *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(SK3VERTEX), (VOID *)sizeof(VEC));
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(SK3VERTEX), (VOID *)(sizeof(VEC) + sizeof (VEC2)));
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(SK3VERTEX), (VOID *)(2 * sizeof(VEC) + sizeof (VEC2)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);


  glBindVertexArray(0);

  /* Indexes */
  if (Ind != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Pr->NumOfI = NumOfI;
  }
  else
    Pr->NumOfI = NumOfV;

  Pr->Trans = MatrIdentity();
  return TRUE;
} /* End of 'SK3_RndPrimCreate' function */

/* Delete primitive function.
 * ARGUMENTS:
 *  - point to primitive have to deleted:
 *      SK3PRIM *P;
 * RETURNS: None.
*/
VOID SK3_RndPrimFree( SK3PRIM *Pr ) 
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
  if (Pr->IBuf != 0)
    glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(SK3PRIM));
} /* End of 'SK3_RndPrimFree' function */

/* Draw primitive function.
 * ARGUMENTS:
 *  - point to primitive:
 *      SK3PRIM *P;
 *  - Matrix of world transformation:
 *      MATR World;
 * RETURNS: None.
*/
VOID SK3_RndPrimDraw( SK3PRIM *Pr, MATR World )
{
  INT
    loc,
    PrimType =
      Pr->Type == SK3_PRIM_POINTS ? GL_POINTS :
      Pr->Type == SK3_PRIM_LINES  ? GL_LINES :
      Pr->Type == SK3_PRIM_TRIMESH  ? GL_TRIANGLES : GL_POINTS;
  MATR 
    W = MatrMulMatr(Pr->Trans, World),
    WVP = MatrMulMatr(W, SK3_RndMatrVP),
    MatrN = MatrTranspose(MatrInverse(W));
  UINT Prog;

  glLoadMatrixf(WVP.M[0]);

  /* Draw triangles */
  glBindVertexArray(Pr->VA);

  Prog = SK3_RndMaterialApply(Pr->MtlNo);

  glUseProgram(Prog);

  /* Setup transform coefficients */
  if ((loc = glGetUniformLocation(Prog, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, WVP.M[0]);
  if ((loc = glGetUniformLocation(Prog, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, W.M[0]);
  if ((loc = glGetUniformLocation(Prog, "MatrN")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, MatrN.M[0]);
  if ((loc = glGetUniformLocation(Prog, "Time")) != -1)
    glUniform1f(loc, SK3_Anim.Time);
  if ((loc = glGetUniformLocation(Prog, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &SK3_RndCamLoc.X);
  /*if ((loc = glGetUniformLocation(SK3_RndProgId, "CamDir")) != -1)
    glUniform3fv(loc, 1, &SK3_RndCamDir.X);
  if ((loc = glGetUniformLocation(SK3_RndProgId, "CamUp")) != -1)
    glUniform3fv(loc, 1, &SK3_RndCamUp.X);
  if ((loc = glGetUniformLocation(SK3_RndProgId, "CamRight")) != -1)
    glUniform3fv(loc, 1, &SK3_RndCamRight.X);*/

  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(PrimType, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    glDrawArrays(PrimType, 0, Pr->NumOfI);

  /* Draw normals */
  //if (GetAsyncKeyState(VK_RMENU) & 0x8000)
  //{
  //  glBindVertexArray(Pr->NormVA);
  //  glDrawArrays(GL_LINES, 0, Pr->NumOfN * 2);
  //}
  glUseProgram(0);

  glBindVertexArray(0);
} /* End of 'SK3_RndPrimDraw' function */

/* Set normals function.
 * ARGUMENTS:
 *  - point to vertex:
 *      SK3VERTEX *V;
 *  - count of vertex:
 *      INT NumOfV;
 *  - array of indexes:
 *      INT *Ind;
 *  - count of indexes:
 *      INT NumOfI;
 * RETURNS: None.
*/
static VOID SK3_RndPrimTrimeshAutonormals( SK3VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  INT i;

  for (i = 0; i < NumOfV; i++)
    V[i].N = VecSet(0, 0, 0);

  for (i = 0; i < NumOfI; i+= 3)
  {
    VEC
      P0 = V[Ind[i]].P,
      P1 = V[Ind[i + 1]].P,
      P2 = V[Ind[i + 2]].P,
      S1 = VecSubVec(P1, P0),
      S2 = VecSubVec(P2, P0),
      N = VecNormalize(VecCrossVec(S1, S2));
    INT
      n0 = Ind[i],
      n1 = Ind[i + 1],
      n2 = Ind[i + 2];

    V[n0].N = VecAddVec(V[n0].N, N);
    V[n1].N = VecAddVec(V[n1].N, N);
    V[n2].N = VecAddVec(V[n2].N, N);
  }

  for (i = 0; i < NumOfV; i++)
    V[i].N = VecNormalize(V[i].N);
} /* End of 'SK3_RndPrimTrimeshAutonormals' function */

/* Load primitive function.
 * ARGUMENTS:
 *  - point to new primitive:
 *      SK3PRIM *P;
 *  - type of this primitive:
 *      SK3PRIM_TYPE Type;
 *  - file name:
 *      CHAR *FileName;
 * RETURNS:
 *  (BOOL) load result.
*/
BOOL SK3_RndPrimLoad( SK3PRIM *Pr, SK3PRIM_TYPE Type, CHAR *FileName ) 
{
  INT nv, ni, size, *I;
  SK3VERTEX *V;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(SK3PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      ni += 3;

  size = sizeof(SK3VERTEX) * nv + sizeof(INT) * ni;

  V = malloc(size);
  if (V == NULL)
    return FALSE;

  memset(V, 0, size);

  I = (INT *)(nv + V);

  /* Load primitive data */
  rewind(F);
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf(Buf + 2, "%f%f%f", &x, &y, &z);
      V[nv].P = VecSet(x, y, z);
      V[nv].T = Vec2Set(1, 1);
      V[nv].N = VecSet(1, 1, 1);
      V[nv++].C = Vec4Set(1, 1, 1, 1);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);

      I[ni++] = n1 - 1;
      I[ni++] = n2 - 1;
      I[ni++] = n3 - 1;
    }

  fclose(F);

  SK3_RndPrimTrimeshAutonormals(V, nv, I, ni);
  SK3_RndPrimCreate(Pr, V, nv, I, ni);
  Pr->Type = Type;
  free(V);

  return TRUE;
} /* End of 'SK3_RndPrimLoad' function */

/* END OF 'RNDPRIM.C' FILE */
