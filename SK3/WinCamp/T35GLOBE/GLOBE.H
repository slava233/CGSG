/* FILE NAME: GLOBE.H
 * PROGRAMMER: SK3
 * DATE: 06.01.2019
 * PURPOSE: Draw sphere header file
 */

#ifndef __GLOBE_H_
#define __GLOBE_H_

#include "timer.h" 

/* PI math constant*/
#define PI       3.14159265358979323846

/* Degrees to radians conversion macro */
#define D2R(X) ((X) * PI / 180)

/* Vector struct */
typedef struct
{
  DOUBLE X, Y, Z; /* Vector coordinates */
} VEC;

/* Coordinate translation init function.
 * Arguments:
 *   - Angle to rotate to:
 *      DOUBLE Angle;
 * RETURN:
 *   NONE
 */
VOID GLB_Init( DOUBLE Angle );

/* Draw sphere funciton.
 * Arguments:
 *   - DC handle:
 *      HDC hDC;
 *   - size of screen:
 *      INT W, INT H;
 * RETURN:
 *   NONE;
 */
VOID GLB_Draw( HDC hDC, INT W, INT H );

#endif /* __GLOBE_H_ */

/* END OF 'GLOBE.H' FILE */
