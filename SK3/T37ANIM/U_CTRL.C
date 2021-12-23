 /* FILE NAME: U_CTRL.C
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: Animation system
 *          Sample units
 *          Unit control
 */

#include "units.h"

/* type for unit control */
typedef struct
{
  SK3_UNIT_BASE_FIELDS;
  VEC CamDir, CamLoc;       /* direction of camera look and camera position */
  FLT Rdx, Rdy, Rdz;        /* identity of rotate */
  FLT Rx, Ry, Rz;           /* delta rotate */
  VEC TransformedCamLoc;    /* vector for transformed camera location */
} SK3UNIT_CTRL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT_CTRL *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitInit( SK3UNIT_CTRL *Uni, SK3ANIM *Ani )
{
  Uni->CamDir = VecSet(1, 0, 0);
  Uni->CamLoc = VecSet(0, 700, 0);
  Uni->Rdx = Uni->Rdy = Uni->Rdz = 2;
  Uni->TransformedCamLoc = Uni->CamLoc;
} /* End of 'SK3_UnitInit' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       SK3UNIT_CTRL *Uni;
 *   - animation context:
 *       SK3ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK3_UnitResponse( SK3UNIT_CTRL *Uni, SK3ANIM *Ani )
{
  if (Ani->Keys[VK_ESCAPE])
    exit(0);
  else if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  else if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['R'])
  {
    if (Ani->IsWireFrame)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Ani->IsWireFrame = !Ani->IsWireFrame;
  }
  else if (Ani->Keys['F'])
    FlipFullScreen();
  else if (Ani->Keys[VK_LEFT] || Ani->Keys[VK_RIGHT])
    Uni->Ry += Uni->Rdy * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]);
  else if (Ani->Keys[VK_NEXT])
    Uni->Rz += Uni->Rdz;

  Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->CamDir, 5 * (Ani->Keys[VK_DOWN] - Ani->Keys[VK_UP])));

  SK3_RndCamSet(PointTransform(Uni->CamLoc, MatrRotateY(Uni->Ry)), VecSet(0, 400, 0), VecSet(0, 1, 0));
} /* End of 'SK3_UnitResponse' function */

/* Unit control creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (SK3UNIT *) pointer to created unit.
 */
SK3UNIT * SK3_UnitCreateCtrl( VOID )
{
  SK3UNIT_CTRL *Uni;

  if ((Uni = (SK3UNIT_CTRL *)SK3_AnimUnitCreate(sizeof(SK3UNIT_CTRL))) == NULL)
    return NULL;                                
  /* Setup unit methods */
  Uni->Init = (VOID *)SK3_UnitInit;
  Uni->Response = (VOID *)SK3_UnitResponse;

  return (SK3UNIT *)Uni;
} /* End of 'SK3_UnitCreateCtrl' function */

/* END OF 'U_COW.C' FILE */
