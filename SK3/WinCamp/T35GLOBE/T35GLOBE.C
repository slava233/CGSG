/* FILE NAME: T35GLOBE.C
 * PROGRAMMER: SK3
 * DATE: 06.01.2019
 * PURPOSE: Draw sphere main module
 */

#include <time.h>

#include "globe.h"

#define WND_CLASS_NAME "My window class"

/* Purpose of MainWindowFunc function.
 * Arguments:
 *   - window handle:
 *       HWND hWND;
 *   -  unsigned int message:
 *       UINT Msg;
 *   - WORD parametr(value):
 *       WPARAM wParam;
 *   - LONG parametr(value):
 *       LPARAM lParam;
 * RETURN:
 *   (LRESULT) message from window code.
 */
LRESULT CALLBACK MainWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  LPSYSTEMTIME t = NULL;
  HBRUSH hBr, hOldBr;
  static INT w, h;
  static HDC hMemDC;
  static HBITMAP hBm;
  static CHAR Buf[300];
  static BITMAP bm;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);

    SetTimer(hWnd, 47, 2, NULL);
    GLB_TimerInit();
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);

    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);

    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_TIMER:
    GLB_TimerResponce();

    /* Clear background */
    hBr = CreateSolidBrush(RGB(255, 255, 255));
    hOldBr = SelectObject(hMemDC, hBr);
    Rectangle(hMemDC, 0, 0, w + 1, h + 1);
    SelectObject(hMemDC, hOldBr);
    DeleteObject(hBr);

    /* Draw sphere */
    GLB_Init(GLB_Time * 30);
    GLB_Draw(hMemDC, w, h);

    SetTextColor(hMemDC, RGB(255, 0, 0));
    SetBkMode(hMemDC, TRANSPARENT);
    TextOut(hMemDC, 10, 10, Buf, sprintf(Buf, "FPS: %f", GLB_FPS));

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_KEYDOWN:
    if (wParam == 'P')
      GLB_IsPause = !GLB_IsPause;
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    /* Blit frame to window */
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_CLOSE:
    if (MessageBox(NULL, "Are you sure you want to exit?", "EXIT", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
      return 0;
    break;
  case WM_DESTROY:
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    KillTimer(hWnd, 47);
    PostQuitMessage(47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MainWindowFunc' function */

/* Purpose of WinMain.
 * Arguments:
 *   - instance handle:
 *       HINSTANCE hInstance;
 *   - prev instance hadle (not use):
 *       HISTANCE hPrevInsatnce;
 *   - Command prompt:
 *       CHAR *CmdLine;
 *   - Show window flag:
 *       INT ShowCmd;
 * RETURN:
 *   (INT) return to windows code.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInsatnce, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS cs;
  HWND hWnd;
  MSG msg;

  cs.style = CS_VREDRAW | CS_HREDRAW;
  cs.cbClsExtra = 0;
  cs.cbWndExtra = 0;
  cs.hInstance = hInstance;
  cs.hIcon = LoadIcon(NULL, IDI_SHIELD);
  cs.hCursor = LoadCursor(NULL, IDC_CROSS);
  cs.hbrBackground = (HBRUSH)COLOR_WINDOW;
  cs.lpszMenuName = NULL;
  cs.lpszClassName = WND_CLASS_NAME;
  cs.lpfnWndProc = MainWindowFunc;
  
  if (!RegisterClass(&cs))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONSTOP);
    return 0;
  }

  hWnd = 
    CreateWindow(WND_CLASS_NAME,
      "...",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else 
      SendMessage(hWnd, WM_TIMER, 0, 0);
  return msg.wParam;
} /* End of 'WinMain' function */

/* END OF 'T35GLOBE.C' FILE */

