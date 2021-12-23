/* FILE NAME: TIMER.H
 * PROGRAMMER: SK3
 * DATE: 06.01.2019
 * PURPOSE: Timer declaration module
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include <commondf.h> 

/***
 *  Global timer variables 
 ***/

DOUBLE 
  GLB_Time,       /* Time from program start in seconds */
  GLB_DeltaTime,  /* time between two frames in seconds */
  GLB_FPS;        /* Frames per second */
BOOL GLB_IsPause; /* Pause flag */

/* Timer init function.
 * Arguments:
 *   - NONE
 * RETURN:
 *   NONE
 */
VOID GLB_TimerInit( VOID );

/* Response timer funciton.
 * Arguments:
 *   NONE;
 * RETURN:
 *   NONE;
 */
VOID GLB_TimerResponce( VOID );

#endif /* __TIMER_H_ */

/* END OF 'TIMER.H' FILE */
