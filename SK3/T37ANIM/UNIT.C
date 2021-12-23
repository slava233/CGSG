/* FILE NAME: T36ANIM.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Base unit support functions
 */

#include "units.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitInit( SK3UNIT *Uni, SK3ANIM *Ani )
{
} /* End of 'SK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitClose( SK3UNIT *Uni, SK3ANIM *Ani )
{
} /* End of 'SK3_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitResponse( SK3UNIT *Uni, SK3ANIM *Ani )
{
} /* End of 'SK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitRender( SK3UNIT *Uni, SK3ANIM *Ani )
{
} /* End of 'SK3_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_AnimUnitCreate( INT Size )
{
  SK3UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(SK3UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = SK3_UnitInit;
  Uni->Close = SK3_UnitClose;
  Uni->Response = SK3_UnitResponse;
  Uni->Render = SK3_UnitRender;
  return Uni;
} /* End of 'SK3_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */
