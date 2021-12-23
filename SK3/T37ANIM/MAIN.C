/* FILE NAME: MAIN.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Window depended
 *          Start of program
 */

#include <time.h>

#include "units.h"

/* Name of window class */
#define SK3_WND_CLASS_NAME "CGSG'2019 WinterCamp Class Name"

/* Main window message handle function.
 * ARGUMENTS:
 *  - window handle:
 *      HWND hWnd;
 *  - message identifier:
 *      UINT Msg;
 *  - message first parameter:
 *      WPARAM wParam;
 *  - message second parameter:
 *      LPARAM lParam;
 * RETURNS:
 *  (LRESULT) Message returns code;
 */
LRESULT CALLBACK MainWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *  - handle of application instance:
 *      HINSTANCE hInstance;
 *  - dummy handle of previous application instance (not used):
 *      HINSTANCE hPrevInstance;
 *  - command line string
 *      CHAR *CmdLine;
 *  - show window command parameter:
 *      INT CmdShow;
 * RETURNS:
 *  (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS cs;
  HWND hWnd;
  MSG msg = {0};

  SetDbgMemHooks();

  /* Class initialising */
  cs.style = CS_VREDRAW | CS_HREDRAW;
  cs.cbClsExtra = 0;
  cs.cbWndExtra = 0;
  cs.hbrBackground = (HBRUSH)COLOR_WINDOW;
  cs.hCursor = LoadCursor(NULL, IDC_ARROW);
  cs.hIcon = LoadIcon(NULL, IDI_ERROR);
  cs.hInstance = hInstance;
  cs.lpfnWndProc = MainWindowFunc;
  cs.lpszMenuName = NULL;
  cs.lpszClassName = SK3_WND_CLASS_NAME;

  /* Registration */
  if (!RegisterClass(&cs))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Making window */
  hWnd = 
    CreateWindowA(SK3_WND_CLASS_NAME,
                  "CGSG FOREVER",
                  WS_OVERLAPPEDWINDOW,
                  CW_USEDEFAULT, CW_USEDEFAULT,
                  CW_USEDEFAULT, CW_USEDEFAULT,
                  NULL,
                  NULL,
                  hInstance,
                  NULL);

  SK3_AnimAddUnit(SK3_UnitCreateCow());
  SK3_AnimAddUnit(SK3_UnitCreateCtrl());

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
    {
      SendMessage(hWnd, WM_TIMER, 47, 0);
    }
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Main window message handle function.
 * ARGUMENTS:
 *  - window handle:
 *      HWND hWnd;
 *  - message identifier:
 *      UINT Msg;
 *  - message first parameter:
 *      WPARAM wParam;
 *  - message second parameter:
 *      LPARAM lParam;
 * RETURNS:
 *  (LRESULT) Message returns code;
 */
LRESULT CALLBACK MainWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static CHAR Buf[300];

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    SetTimer(hWnd, 47, 8, NULL);
    SK3_AnimInit(hWnd);
    return 0;
  case WM_SIZE:
    SK3_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_ERASEBKGND:
    return 3;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    SK3_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;
  case WM_TIMER:
    SK3_AnimRender();
    sprintf(Buf, "FPS: %lf", SK3_Anim.FPS);
    SetWindowText(hWnd, Buf);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
    SK3_AnimClose();
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MainWindowFunc' function */

/* END OF 'MAIN.C' FILE */
