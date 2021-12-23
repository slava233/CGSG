/* FILE NAME: RNDDATA.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Data for rendering
 */

#include "rnd.h"

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")


/* Projection data */
FLT
  SK3_RndProjSize,     /* Project plane unit square size */
  SK3_RndProjDist,     /* Distance to project plane (near) */
  SK3_RndProjFarClip;  /* Distance to project far clip plane (far) */
INT
  SK3_RndFrameW, SK3_RndFrameH; /* Viewport size */

/* Transformation matrix /*/
MATR
  SK3_RndMatrView, /* View coordinate system matrix */
  SK3_RndMatrProj, /* Projection matrix */
  SK3_RndMatrVP;   /* Precalculated matrix multiplication View by Proj */

/* Camera parameters */
VEC
  SK3_RndCamLoc,   /* Camera position */
  SK3_RndCamUp,    /* Camera up direction */
  SK3_RndCamDir,   /* Camera direction to object */
  SK3_RndCamRight, /* Camera right direction */
  SK3_RndCamAt;

/* OpenGL support */
HDC SK3_hRndDC;     /* Back frame buffer device context */
HWND SK3_hRndWnd;   /* Work window */
HGLRC SK3_hRndGLRC; /* OpenGL rendering context */

UINT SK3_RndProgId; /* Program for shaders identifier */

/* END OF 'RNDDATA.C' FILE */
