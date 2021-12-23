/* FILE NAME: U_COW.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Sample units
 *          Unit cow
 */

#include "units.h"

/* Type for cow unit */
typedef struct
{
  SK3_UNIT_BASE_FIELDS;
  SK3PRIM Cow;          /* Primitive of cow */
} SK3UNIT_COW;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitInit( SK3UNIT_COW *Uni, SK3ANIM *Ani )
{
  SK3_RndPrimLoad(&Uni->Cow, SK3_PRIM_TRIMESH, "Dark Knight.obj");
} /* End of 'SK3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitClose( SK3UNIT_COW *Uni, SK3ANIM *Ani )
{
  SK3_RndPrimFree(&Uni->Cow);
} /* End of 'SK3_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitResponse( SK3UNIT_COW *Uni, SK3ANIM *Ani )
{
  Uni->Cow.Trans = MatrRotateY(0);
} /* End of 'SK3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitRender( SK3UNIT_COW *Uni, SK3ANIM *Ani )
{
  SK3_RndPrimDraw(&Uni->Cow, /*MatrIdentity()*/MatrScale(VecSet(4, 4, 4)));
} /* End of 'SK3_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_UnitCreateCow( VOID )
{
  SK3UNIT_COW *Uni;

  if ((Uni = (SK3UNIT_COW *)SK3_AnimUnitCreate(sizeof(SK3UNIT_COW))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)SK3_UnitInit;
  Uni->Response = (VOID *)SK3_UnitResponse;
  Uni->Render = (VOID *)SK3_UnitRender;
  Uni->Close = (VOID *)SK3_UnitClose;

  return (SK3UNIT *)Uni;
} /* End of 'SK3_UnitCreateBall' function */

/* END OF 'U_COW.C' FILE */
