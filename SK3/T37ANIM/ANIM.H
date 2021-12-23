/* FILE NAME: ANIM.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: MAIN DECLARATION MODULE
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "rnd.h"

/* Max count of units */
#define SK3_MAX_UNITS 3000

/* Elements of standart units */
#define SK3_UNIT_BASE_FIELDS \
  VOID (*Init)( SK3UNIT *Uni, SK3ANIM *Ani );      \
  VOID (*Close)( SK3UNIT *Uni, SK3ANIM *Ani );     \
  VOID (*Response)( SK3UNIT *Uni, SK3ANIM *Ani );  \
  VOID (*Render)( SK3UNIT *Uni, SK3ANIM *Ani )

/* Type of animation context */
typedef struct tagSK3ANIM SK3ANIM;

/* Type of standart unit */
typedef struct tagSK3UNIT SK3UNIT;

/* Type of animation context */
struct tagSK3ANIM
{
  HWND hWnd;                     /* Window */
  HDC hDC;                       /* Context of window */
  INT W, H;                      /* Window properties */

  SK3UNIT *Units[SK3_MAX_UNITS]; /* Array of animation objects */
  INT NumOfUnits;                /* Count of animation objects */

  /* System input and output */
  FLT
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  /* Keyboard utils */
  BYTE Keys[256];                /* Array for current buttons state */
  BYTE KeysOld[256];             /* Array for last buttons state */
  BYTE KeysClick[256];           /* Array for click-state of buttons */

  /* Mouse utils */
  INT Mx, My,                    /* Cursour position */
      Mdx, Mdy,                  /* Delta positions current and last */
      Mz, Mdz;                   /* Wheel state and delta */

  BOOL IsWireFrame;               /* Wireframe flag */
};

/* Type of standart unit */
struct tagSK3UNIT
{
  SK3_UNIT_BASE_FIELDS;
};

/* Main context */
extern SK3ANIM SK3_Anim;

/* Initialisation animation function.
 * ARGUMENTS:
 *  - window handle:
 *      HWND hWnd;
 * RETURNS: None.
 */
VOID SK3_AnimInit( HWND hWnd );

/* End of use animation function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimClose( VOID );

/* Resize function.
 * ARGUMENTS:
 *  - New window properties:
 *       INR W, H;
 * RETURNS: None.
 */
VOID SK3_AnimResize( INT W, INT H );

/* Copy frame in memory to frame in window function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimCopyFrame( VOID );

/* Main rendering function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID SK3_AnimRender( VOID );

/* Set screen full function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID FlipFullScreen( VOID );

/* Add new unit function.
 * ARGUMENTS:
 *  - new unit:
 *      SK3UNIT *Uni;
 * RETURNS: None.
 */
VOID SK3_AnimAddUnit( SK3UNIT *Uni );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
