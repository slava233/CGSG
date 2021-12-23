/* FILE NAME: RNDRES.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Resource declaration
 */

#ifndef __RNDRES_H_
#define __RNDRES_H_

#include "anim.h"

/* Maximum material name size */
#define SK3_MATERIAL_NAME_SIZE  300

/* Maximum resource tables size */
#define SK3_RESOURCE_TABLE_SIZE 3000

/* Rendering resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndResInit( VOID );

/* Rendering resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndResClose( VOID );

/***
 * Shader handle function group
 ***/

/* Shader store representation type */
typedef struct tagSK3SHADER
{
  CHAR Name[SK3_MATERIAL_NAME_SIZE]; /* Shader path prefix name */
  UINT PrgNo;                        /* OpenGL shader program Id */
} SK3SHADER;

/* Shader resource table and size */
extern SK3SHADER SK3_RndShaders[SK3_RESOURCE_TABLE_SIZE];
extern INT SK3_RndShadersSize;

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT SK3_RndShaderLoad( CHAR *FileNamePrefix );

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID SK3_RndShaderFree( UINT Prg );

/* Add shader program from file function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader table index or -1 if error is occured.
 */
INT SK3_RndShaderAdd( CHAR *FileNamePrefix );

/* Update all shaders from store table function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID SK3_RndShadersUpdate( VOID );

/* Remove shader program from resource table function.
 * ARGUMENTS:
 *   - shader table index:
 *       INT ShdNo;
 * RETURNS: None.
 */
VOID SK3_RndShaderDelete( INT ShdNo );

/***
 * Texture handle function group
 ***/

/* Texture store representation type */
typedef struct tagSK3TEXTURE
{
  CHAR Name[SK3_MATERIAL_NAME_SIZE]; /* Image file name */
  INT W, H;                          /* Texture size in pixels */
  UINT TexId;                        /* OpenGL texture Id */
} SK3TEXTURE;

/* Texture resource table and size */
extern SK3TEXTURE SK3_RndTextures[SK3_RESOURCE_TABLE_SIZE];
extern INT SK3_RndTexturesSize;

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) texture table index or -1 if error is occured.
 */
INT SK3_RndTextureAddFromFile( CHAR *FileName );

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
INT SK3_RndTextureAdd( CHAR *Name, INT W, INT H, VOID *ImageData );

/* Remove texture from resource table function.
 * ARGUMENTS:
 *   - texture table index:
 *       INT TexNo;
 * RETURNS: None.
 */
VOID SK3_RndTextureDelete( INT TexNo );

/***
 * Material handle function group
 ***/

/* Material store representation type */
typedef struct tagSK3MATERIAL
{
  CHAR Name[SK3_MATERIAL_NAME_SIZE]; /* Material name */

  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;                    /* Ambient, diffuse, specular coefficients */
  FLT Ph;                            /* Phong power coefficient */
  FLT Trans;                         /* Transparency factor */
  INT Tex[8];                        /* Texture references from texture table */
  INT ShdNo;                         /* Shader reference in shader table */
} SK3MATERIAL;

/* Material resource table and size */
extern SK3MATERIAL SK3_RndMaterials[SK3_RESOURCE_TABLE_SIZE];
extern INT SK3_RndMaterialsSize;

/* Add material function.
 * ARGUMENTS:
 *   - material data structure pointer:
 *       SK3MATERIAL *Mtl;
 * RETURNS:
 *   (INT) material table index or -1 if error is occured.
 */
INT SK3_RndMaterialAdd( SK3MATERIAL *Mtl );

/* Material apply function.
 * ARGUMENTS:
 *   - material table index:
 *       INT MtlNo;
 * RETURNS:
 *   (UINT) apply result shader program identifier.
 */
UINT SK3_RndMaterialApply( INT MtlNo );

#endif /* __RNDRES_H_ */

/* END OF 'RNDRES.H' FILE */
