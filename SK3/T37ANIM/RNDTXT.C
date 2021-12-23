/* FILE NAME: RNDTXT.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Rendering system
 *          Resource
 *          Texture module
 */

#include <stdio.h>

#include "rnd.h"

/* Texture resource table and size */
SK3TEXTURE SK3_RndTextures[SK3_RESOURCE_TABLE_SIZE];
INT SK3_RndTexturesSize;

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) texture table index or -1 if error is occured.
 */
INT SK3_RndTextureAddFromFile( CHAR *FileName )
{
  INT tex = -1, w = 0, h = 0, x, y;
  DWORD *mem;
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return -1;
  fread(&w, 2, 1, F);
  fread(&h, 2, 1, F);
  if ((mem = malloc(w * h * 4)) != NULL)
  {
    DWORD d = 0;

    for (y = 0; y < h; y++)
      for (x = 0; x < w; x++)
      {
        fread(&d, 3, 1, F);
        d |= 0xFF000000;
        mem[(h - 1 - y) * w + x] = d;
      }
    tex = SK3_RndTextureAdd(FileName, w, h, mem);
    free(mem);
  }
  fclose(F);
  return tex;
} /* End of 'SK3_RndTextureAddFromFile' function */

/* Add texture image by image data function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture image size:
 *       INT W, H;
 *   - texture image pixel color data (DWORD colors):
 *       VOID *ImageData;
 * RETURNS:
 *   (INT) texture table index or -1 if error is occured.
 */
INT SK3_RndTextureAdd( CHAR *Name, INT W, INT H, VOID *ImageData )
{
  if (SK3_RndTexturesSize >= SK3_RESOURCE_TABLE_SIZE)
    return -1;

  /* Allocate texture space */
  glGenTextures(1, &SK3_RndTextures[SK3_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, SK3_RndTextures[SK3_RndTexturesSize].TexId);

  /* Upload texture */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, ImageData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  strncpy(SK3_RndTextures[SK3_RndTexturesSize].Name, Name, SK3_MATERIAL_NAME_SIZE - 1);
  SK3_RndTextures[SK3_RndTexturesSize].W = W;
  SK3_RndTextures[SK3_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return SK3_RndTexturesSize++;
} /* End of 'SK3_RndTextureAdd' function */

/* Remove texture from resource table function.
 * ARGUMENTS:
 *   - texture table index:
 *       INT TexNo;
 * RETURNS: None.
 */
VOID SK3_RndTextureDelete( INT TexNo )
{
  if (TexNo < 0 || TexNo >= SK3_RndTexturesSize)
    return;
  glDeleteTextures(1, &SK3_RndTextures[TexNo].TexId);
  memset(&SK3_RndTextures[TexNo], 0, sizeof(SK3TEXTURE));
} /* End of 'SK3_RndTextureDelete' function */

/* END OF 'RNDTXT.C' FILE */
