/* FILE NAME: RNDBASE.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Base function for rendering
 */

#include <time.h>

#include "rnd.h"

/* Projection set function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
static VOID SK3_RndProjSet( VOID )
{
  FLT ratio_x, ratio_y;

  ratio_x = ratio_y = SK3_RndProjSize / 2;
  if (SK3_RndFrameW > SK3_RndFrameH) 
    ratio_x *= (FLT)SK3_RndFrameW / SK3_RndFrameH;
  else
    ratio_y *= (FLT)SK3_RndFrameH / SK3_RndFrameW;

  SK3_RndMatrProj =
    FrustumMatr(-ratio_x, ratio_x, -ratio_y, ratio_y,
      SK3_RndProjDist, SK3_RndProjFarClip);
  SK3_RndMatrVP = MatrMulMatr(SK3_RndMatrView, SK3_RndMatrProj);
}

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
VOID SK3_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  SK3_RndMatrView = MatrView(Loc, At, Up1);
  SK3_RndMatrVP = MatrMulMatr(SK3_RndMatrView, SK3_RndMatrProj);

  SK3_RndCamLoc = Loc;
  SK3_RndCamUp = VecSet(SK3_RndMatrView.M[0][1], SK3_RndMatrView.M[1][1], SK3_RndMatrView.M[2][1]);
  SK3_RndCamDir = VecSet(-SK3_RndMatrView.M[0][2], -SK3_RndMatrView.M[1][2], -SK3_RndMatrView.M[2][2]);
  SK3_RndCamRight = VecSet(SK3_RndMatrView.M[0][0], SK3_RndMatrView.M[1][0], SK3_RndMatrView.M[2][0]);
  SK3_RndCamAt = At;
} /* End of 'SK3_RndCamSet' function */

/* Resize window in memory function.
 * ARGUMENTS:
 *  - new window properties:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID SK3_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* Setup projection */
  SK3_RndFrameW = W;
  SK3_RndFrameH = H;
  SK3_RndProjSet();
} /* End of 'SK3_RndResize' function */

/* Initialisation OGL function.
 * ARGUMENTS:
 *  - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID SK3_RndInit( HWND hWnd )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  SK3_hRndDC = GetDC(SK3_hRndWnd = hWnd);
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(SK3_hRndDC, &pfd);
  DescribePixelFormat(SK3_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(SK3_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  SK3_hRndGLRC = wglCreateContext(SK3_hRndDC);
  wglMakeCurrent(SK3_hRndDC, SK3_hRndGLRC);

  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    exit(0);

  /* Setup default values */
  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);

  SK3_RndProjDist = 0.1;
  SK3_RndProjFarClip = 2000.0;
  SK3_RndProjSize = SK3_RndProjDist;

  SK3_RndFrameW = 47;
  SK3_RndFrameH = 47;
  SK3_RndProjSet();
  SK3_RndCamSet(VecSet(18, 18, 18), VecSet(0, 0, 0), VecSet(0, 1, 0));

  SK3_RndResInit();
} /* End of 'SK3_RndInit' function */

/* End of use OGL function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(SK3_hRndGLRC);
  SK3_RndResClose();
  ReleaseDC(SK3_hRndWnd, SK3_hRndDC);
} /* End of 'SK3_RndClose' function */

/* Start of rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndStart( VOID )
{
  LONG t = clock();
  static LONG ReloadStart;

  /* Reload shader */
  if (ReloadStart == 0)
    ReloadStart = t;
  if (t - ReloadStart > 3 * CLOCKS_PER_SEC)
  {
    ReloadStart = t;

    SK3_RndShadersUpdate();
  }

  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

} /* End of 'SK3_RndStart' function */

/* Copy frame in memory to frame in window function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndCopyFrame( VOID )
{
  SwapBuffers(SK3_hRndDC);
} /* End of 'SK3_RndCopyFrame' function */

/* End of rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_RndEnd( VOID )
{
  glFinish();
} /* End of 'SK3_RndEnd' function */

/* END OF 'RNDBASE.C' FILE */
