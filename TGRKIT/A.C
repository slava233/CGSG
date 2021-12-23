#include <stdlib.h>
#include <conio.h>

#include <tgrp.h>

void main( void )
{
  int x, y;

  TGR_InitLibStatic();
  TGR_InitMode(640, 480, 32);
  for (y = 0l; y < 256; y++)
    for (x = 0; x < 256; x++)
      TGR_PutPixel(100 + x, 100 + y, TGR_RGB(x, 255 - y, (y + x) / 2));
  TGR_CursorShow();
  while (!kbhit())
  {
    TGR_MouseGetData();
    TGR_CursorMove(TGR_MouseX, TGR_MouseY);
    TGR_PutPixel(rand() % TGR_GetWidth(), rand() % TGR_GetHeight(),
      TGR_RGB(rand() & 255, rand() & 255, rand() & 255));
    TGR_PutBar(rand() % TGR_GetWidth(), rand() % TGR_GetHeight(),
      30, 30,
      TGR_RGB(rand() & 255, rand() & 255, rand() & 255));
    TGR_Set
    TGR_PutString(rand() % TGR_GetWidth(), rand() % TGR_GetHeight(),
      "Vasja & Вася");
    if (TGR_MouseButtons & 1)
      TGR_PutPixel(TGR_MouseX, TGR_MouseY, TGR_RGB(255, 255, 255));
    if (TGR_MouseButtons & 2)
      TGR_Fill(0);
  }
  getch();
  TGR_CursorHide();
  TGR_CloseLib();
}