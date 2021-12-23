/* FILE NAME: RNDMTL.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Rendering system
 *          Resource
 *          Texture module
 */

#include "rnd.h"

/* Material resource table and size */
SK3MATERIAL SK3_RndMaterials[SK3_RESOURCE_TABLE_SIZE];
INT SK3_RndMaterialsSize;

/* Add material function.
 * ARGUMENTS:
 *   - material data structure pointer:
 *       SK3MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table index or -1 if error is occured.
 */
INT SK3_RndMaterialAdd( SK3MATERIAL *Mtl )
{
  INT i;

  /* Look for exists material */
  for (i = 0; i < SK3_RndMaterialsSize; i++)
    if (strcmp(SK3_RndMaterials[i].Name, Mtl->Name) == 0)
      break;

  if (i >= SK3_RESOURCE_TABLE_SIZE)
    return -1;

  SK3_RndMaterials[SK3_RndMaterialsSize] = *Mtl;
  return SK3_RndMaterialsSize++;
} /* End of 'SK3_RndMaterialAdd' function */

/* Material apply function.
 * ARGUMENTS:
 *   - material table index:
 *       INT MtlNo;
 * RETURNS:
 *   (UINT) apply result shader program identifier.
 */
UINT SK3_RndMaterialApply( INT MtlNo )
{
  INT loc, i;
  SK3MATERIAL *mtl;
  UINT ProgId;

  /* Correct material number */
  if (MtlNo < 0 || MtlNo >= SK3_RndMaterialsSize)
    MtlNo = 0;
  mtl = &SK3_RndMaterials[MtlNo];

  /* Correct shader number */
  if (mtl->ShdNo < 0 || mtl->ShdNo >= SK3_RndShadersSize)
    ProgId = SK3_RndShaders[0].PrgNo;
  else
    ProgId = SK3_RndShaders[mtl->ShdNo].PrgNo;

  glUseProgram(ProgId);

  /* Setup illumination coefficients */
  if ((loc = glGetUniformLocation(ProgId, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(ProgId, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(ProgId, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(ProgId, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(ProgId, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Texture apply */
  for (i = 0; i < 8; i++)
  {
    BOOL is = FALSE;
    static CHAR TexName[] = "IsTexture0";

    TexName[sizeof(TexName) - 2] = '0' + i;
    glActiveTexture(GL_TEXTURE0 + i);
    if (mtl->Tex[i] >= 0 && mtl->Tex[i] < SK3_RndTexturesSize)
    {
      is = TRUE;
      glBindTexture(GL_TEXTURE_2D, SK3_RndTextures[mtl->Tex[i]].TexId);
    }
    else
      glBindTexture(GL_TEXTURE_2D, 0);
    if ((loc = glGetUniformLocation(ProgId, TexName)) != -1)
      glUniform1i(loc, is);
  }
  return ProgId;
} /* End of 'SK3_RndMaterialApply' function */

/* END OF 'RNDMTL.C' FILE */
