/***************************************************************
 * Copyright (C) 2012
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : GLIB.H
 * PURPOSE     : Graphics library.
 *               Olympiad purpose declaration module.
 * PROGRAMMER  : VG4.
 * LAST UPDATE : 18.11.2012
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _GLIB_H_
#define _GLIB_H_

/* Set graphics mode function (0 - text, 1 - 640x480 graphics) */
void SetMode( int Mode );

/* Draw line in graphics mode function,
 * arguments - end points coordinates */
void Line( int X0, int Y0, int X1, int Y1 );

#endif /* _GLIB_H_ */

/* END OF 'GLIB.H' FILE */
