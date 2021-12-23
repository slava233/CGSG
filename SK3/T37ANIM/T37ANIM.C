/* FILE NAME: T36ANIM.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: ANIMATIOM SYSTEM
 */

#include <string.h>

#include "anim.h"
#include "timer.h"

/* Main context */
SK3ANIM SK3_Anim;


/* Initialisation animation function.
 * ARGUMENTS:
 *  - window handle:
 *      HWND hWnd;
 * RETURNS: None.
 */
VOID SK3_AnimInit( HWND hWnd )
{
  memset(&SK3_Anim, 0, sizeof(SK3ANIM));

  SK3_Anim.hWnd = hWnd;

  SK3_Anim.NumOfUnits = 0;
  SK3_Anim.IsWireFrame = FALSE;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  SK3_RndInit(hWnd);
  SK3_TimerInit();
  SK3_Anim.hDC = SK3_hRndDC;
} /* End of '' function */

/* End of use animation function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < SK3_Anim.NumOfUnits; i++)
  {
    SK3_Anim.Units[i]->Close(SK3_Anim.Units[i], &SK3_Anim);
    free(SK3_Anim.Units[i]);
  }
  SK3_Anim.NumOfUnits = 0;
  SK3_RndClose();
} /* End of 'SK3_AnimClose' function */

/* Resize function.
 * ARGUMENTS:
 *  - New window properties:
 *       INR W, H;
 * RETURNS: None.
 */
VOID SK3_AnimResize( INT W, INT H )
{
  SK3_Anim.W = W;
  SK3_Anim.H = H;
  SK3_RndResize(W, H);
} /* End of 'SK3_AnimResize' function */

/* Copy frame in memory to frame in window function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimCopyFrame( VOID )
{
  SK3_RndCopyFrame();
} /* End of 'SK3_AnimCopyFrame' function */

/* Set screen full function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; /* Current state */
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* Save last monitor */
    GetWindowRect(SK3_hRndWnd, &SaveRC);

    hmon = MonitorFromWindow(SK3_hRndWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(SK3_hRndWnd, GWL_STYLE), FALSE);

    SetWindowPos(SK3_hRndWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top + 201, SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(SK3_hRndWnd, HWND_TOP,
      SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'FlipFullScreen' function */

/* Main rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimRender( VOID )
{
  INT i;

  SK3_TimerResponse();

  GetKeyboardState(SK3_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    SK3_Anim.Keys[i] >>= 7;
    SK3_Anim.KeysClick[i] = SK3_Anim.Keys[i] && !SK3_Anim.KeysOld[i];
  }
  memcpy(SK3_Anim.KeysOld, SK3_Anim.Keys, 256);

  for (i = 0; i < SK3_Anim.NumOfUnits; i++)
    SK3_Anim.Units[i]->Response(SK3_Anim.Units[i], &SK3_Anim);

  SK3_RndStart();
  for (i = 0; i < SK3_Anim.NumOfUnits; i++)
    SK3_Anim.Units[i]->Render(SK3_Anim.Units[i], &SK3_Anim);
  SK3_RndEnd();
} /* End of 'SK3_AnimRender' function */

/* Add new unit function.
 * ARGUMENTS:
 *  - new unit:
 *      SK3UNIT *Uni;
 * RETURNS: None.
 */
VOID SK3_AnimAddUnit( SK3UNIT *Uni )
{
  SK3_Anim.Units[SK3_Anim.NumOfUnits] = Uni;
  SK3_Anim.Units[SK3_Anim.NumOfUnits]->Init(SK3_Anim.Units[SK3_Anim.NumOfUnits], &SK3_Anim);
  SK3_Anim.NumOfUnits++;
} /* End of 'SK3_AnimAddUnit' function */

/* END OF 'T36ANIM.C' FILE */
