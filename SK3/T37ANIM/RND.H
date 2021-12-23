/* FILE NAME: RND.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: DECLARATION FOR RENDERING MODULE
 */

#ifndef __RND_H_
#define __RND_H_

#define GLEW_STATIC
#include <glew.h>

#include "def.h"
#include "rndres.h"

/* Type for vertex */
typedef struct tagSK3VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} SK3VERTEX;

/* Types of primitive */
typedef enum tagSK3PRIM_TYPE
{
  SK3_PRIM_POINTS, /* Type of primitive, which draws by points */
  SK3_PRIM_LINES,  /* Type of primitive, which draws by lines */
  SK3_PRIM_TRIMESH /* Type of primitive, which draws by triangles */
} SK3PRIM_TYPE;

/* Primitive type */
typedef struct tagSK3PRIM
{
  SK3PRIM_TYPE Type;  /* Type of primitive */
  INT VA, IBuf, VBuf; /* OpenGL vertex array, vertex buffer and index buffer */
  INT NumOfI;         /* Numbner of indexes */
  MATR Trans;         /* Additional transformation matrix */
  INT MtlNo;          /* Material number (from material table) */
} SK3PRIM;

/* Projection data */
extern FLT
  SK3_RndProjSize,     /* Project plane unit square size */
  SK3_RndProjDist,     /* Distance to project plane (near) */
  SK3_RndProjFarClip;  /* Distance to project far clip plane (far) */
extern INT
  SK3_RndFrameW, SK3_RndFrameH; /* Viewport size */

extern FLT
  SK3_RndProjSize,     /* Project plane fit square */
  SK3_RndProjDist,     /* Distance to project plane from viewer (near) */
  SK3_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  SK3_RndMatrView, /* View coordinate system matrix */
  SK3_RndMatrProj, /* Projection coordinate system matrix */
  SK3_RndMatrVP;   /* Stored (View * Proj) matrix */

/* Transformation matrix */
extern MATR
  SK3_RndMatrView, /* View coordinate system matrix */
  SK3_RndMatrProj, /* Projection matrix */
  SK3_RndMatrVP;   /* Precalculated matrix multiplication View by Proj */

/* OpenGL support */
extern HDC SK3_hRndDC;     /* Back frame buffer device context */
extern HWND SK3_hRndWnd;   /* Work window */
extern HGLRC SK3_hRndGLRC; /* OpenGL rendering context */
extern UINT SK3_RndProgId;    /* Program for shaders identifier */

/* Camera parameters */
extern VEC
  SK3_RndCamLoc,
  SK3_RndCamUp,
  SK3_RndCamDir,
  SK3_RndCamRight,
  SK3_RndCamAt;

/***
 * Base render function
 ***/

/* Initialisation OGL function.
 * ARGUMENTS:
 *  - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID SK3_RndInit( HWND hWnd );

/* End of use OGL function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndClose( VOID );

/* Resize window in memory function.
 * ARGUMENTS:
 *  - new window properties:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID SK3_RndResize( INT W, INT H );

/* Copy frame in memory to frame in window function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndCopyFrame( VOID );

/* Start of rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndStart( VOID );

/* End of rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndEnd( VOID );

/* Camera set function.
 * ARGUMENTS:
 *  - vector of camera position:
 *      VEC Loc;
 *  - vector of camera 'look at':
 *      VEC At;
 *  - vector of exemplary direction up of camera:
 *      VEC Up1;
 * RETURNS: None.
 */
VOID SK3_RndCamSet( VEC Loc, VEC At, VEC Up1 );

/***
 * Base function of rendering primitive
 ***/

/* Delete primitive function.
 * ARGUMENTS:
 *  - point to primitive have to deleted:
 *      SK3PRIM *P;
 * RETURNS: None.
*/
VOID SK3_RndPrimFree( SK3PRIM *Pr );

/* Draw primitive function.
 * ARGUMENTS:
 *  - point to primitive:
 *      SK3PRIM *P;
 *  - Matrix of world transformation:
 *      MATR World;
 * RETURNS: None.
*/
VOID SK3_RndPrimDraw( SK3PRIM *Pr, MATR World );

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
BOOL SK3_RndPrimLoad( SK3PRIM *Pr, SK3PRIM_TYPE Type, CHAR *FileName );

/***
 * Shaders support
 ***/

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

#endif /* __RND_H_ */

/* END OF 'RND.H' FILE */
