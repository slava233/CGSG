/* FILE NAME: RNDRES.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Rendering system
 *          Resource
 *          Texture module
 */

#include "rnd.h"

/* Rendering resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndResInit( VOID )
{
  SK3MATERIAL DefMtl =
  {
    "Default material",
    {0.07, 0.07, 0.07}, {1, 0.48, 0.5}, {0.233, 0.233, 0.21569}, 30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    -1
  };
  /* Set all resource tables to zero size */
  SK3_RndMaterialsSize = 0;
  SK3_RndShadersSize = 0;
  SK3_RndTexturesSize = 0;

  /* Load default shader */
  DefMtl.ShdNo = SK3_RndShaderAdd("DEFAULT");

  /* Create default material */
  SK3_RndMaterialAdd(&DefMtl);
} /* End of 'SK3_RndResInit' function */

/* Rendering resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndResClose( VOID )
{
  INT i;

  /* Remove all resources */
  for (i = 0; i < SK3_RndShadersSize; i++)
    SK3_RndShaderDelete(i);
  for (i = 0; i < SK3_RndTexturesSize; i++)
    SK3_RndTextureDelete(i);

  /* Set all resource tables to zero size */
  SK3_RndMaterialsSize = 0;
  SK3_RndShadersSize = 0;
  SK3_RndTexturesSize = 0;
} /* End of 'SK3_RndResClose' function */

/* END OF 'RNDRES.C' FILE */
