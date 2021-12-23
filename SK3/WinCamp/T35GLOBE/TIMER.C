/* FILE NAME: TIMER.C
 * PROGRAMMER: SK3
 * DATE: 06.01.2019
 * PURPOSE: Timer work module
 */
#include <time.h>

#include "timer.h"

/*** 
 *  Semiglobal timer variables
 ***/
static LONG
  StartTime,  /* Program start time in seconds */
  OldTime,    /* Time of previos frame in seconds */
  PauseTime,  /* Time stuck in pause in seconds */
  OldFPSTime, /* Time when last FPS was checked */
  FrameCount; /* Frames counter */

/* Timer init function.
 * Arguments:
 *   - NONE
 * RETURN:
 *   NONE
 */
VOID GLB_TimerInit( VOID )
{
  StartTime = GLB_Time = OldFPSTime = clock();
  PauseTime = 0;
  FrameCount = 0;
  GLB_IsPause = FALSE;
} /* End of 'GLB_TimerInit' function */

/* Response timer funciton.
 * Arguments:
 *   NONE;
 * RETURN:
 *   NONE;
 */
VOID GLB_TimerResponce( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }
  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
} /* End of 'GLB_TimerResponce' function */
 

/* END OF 'TIMER.C' FILE */
