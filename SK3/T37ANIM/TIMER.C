/* FILE NAME: TIMER.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Timer support
 */

#include "timer.h"
#include "anim.h"

static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

/* Start measure function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  SK3_Anim.IsPause = FALSE;
  SK3_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'SK3_TimerInit' function */

/* Response measure function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  SK3_Anim.GlobalTime = (FLT)(t.QuadPart - StartTime) / TimePerSec;
  SK3_Anim.GlobalDeltaTime = (FLT)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (SK3_Anim.IsPause)
  {
    SK3_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    SK3_Anim.DeltaTime = SK3_Anim.GlobalDeltaTime;
    SK3_Anim.Time = (FLT)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    SK3_Anim.FPS = FrameCounter * TimePerSec / (FLT)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'SK3_TimerResponse' function */

/* END OF 'TIMER.C' FILE */
