/* FILE NAME: UNIT.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: UNITS DECLARATION
 */

#ifndef __UNIT_H_
#define __UNIT_H_

#include "def.h"
#include "anim.h"

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_AnimUnitCreate( INT Size );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_UnitCreateCow( VOID );

/* Unit control creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_UnitCreateCtrl( VOID );

#endif /* __UNIT_H_ */

/* END OF 'UNIT.H' FILE */
