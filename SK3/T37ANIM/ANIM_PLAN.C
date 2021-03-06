Animation system
OS	Animation	Application	Render3D
WinMain:
- ����������� ������
  ����
- �������� ����
- ���� ���������
   while (GetMessage(...))
      DispatchMessage(...);

WinFunc:
WM_GETMINMAXINFO:
  . . .
WM_CREATE:
  . . .
WM_SIZE:
  . . .
WM_TIMER:
  . . .
WM_ERASEBKGND:
  . . .
WM_PAINT:
  . . .
WM_DESTROY:
  . . .

Input:
WM_MOUSEWHEEL:
  . . .

	


AnimInit(hWnd);
�������������

AnimClose();
���������������

AnimResize(W, H);
��������� ������� �����

AnimCopyFrame(hDC);
����������� �����

AnimRender();
���������� �����
(����� ��������� �����, ���������� �������, ����� ���� ��������� �������� � ����� � ��� ������� Response, ������� ����� � ����� � ���� ������� �������� Render)


+�������� ��������
ANIM Anim;
	������ ��������� ��������
UNIT:
[

  Init(Anim);
   �������������

  Close(Anim);
   ���������������


  Response(Anim);
������ �������� �������� �� ����� ����� (��������� ����������, ������� � �.�.)

  Render(Anim);
��������� �������� ��������

]

� ������ ������� �������� �������� �������� �������� - Anim - ������� �������� (���������) ��������:
  - ����������
  - ����
  - ��������
  - ������
  - ��������� ����� (...)
  - ��������� ������������ (hDC, ... )	
RndInit(hWnd);

RndClose();

RndResize(W, H);

RndStart();

RndEnd();

RndCopyFrame(hDC);

-----------

RndPrim:
  Create/Load/Free/Draw


��� ������� �������� �������� � ������ ����������?

1.������ ��������� - 
  - ��������� �� ������� Init, Close, Response, Render � ��������� UNIT

������ �����������:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

�.�. � �������� �������� ������ ���������� �� �������� ��������:

#define MAX_UNITS 3000
UNIT *Units[MAX_UNITS];
INT NumOfUnits;

----------------------
����������:
UNIT *Uni = UnitCreateCow();

Anim.Units[Anim.NumOfUnits] = Uni;
Uni->Init(Uni, &Anim);
  ���
    Anim.Units[Anim.NumOfUnits]->Init(Anim.Units[Anim.NumOfUnits], &Anim);
Anim.NumOfUnits++;

� AnimRender � ��������:

  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Render(Anim.Units[i], &Anim);

!!! �������� ������� ���: ������ ��������� ����������� ���������� !!!

��� ���������� ���� ������ ����� ���������� ������������� ���������.

�������� ���:
- ������������ (incapsulation) - �������� ������
- ������������ (iheritance) - ��������� ����� ����� �������� - � ������
- ����������� (polymorph, override) - ��������� ��������� ����������� �������

2.��� ������� ������ (�������� ��������) ������� �������?

��� ������� �������� (UNIT � "����") �������� ��� ��������� � ����� �������.
��� ��� ������ ���� �������� �������� �������� ���������� ���� � ��� ������� � ������� �� �������� ������� ����� ����� ����������� ������� ����� ������� �� ������� 4-�.
��� ������� �� ������� � �������������� ��������� � � ������ ���������� ��������� �� ���� ��������� ������� ��������.


UNIT *Units[MAX_UNITS]:





				












!!! �.�. ������ ������� UNIT-� ������ ��� �������� ���������  �� ������ ���� (self-pointer, � ��++ ��� ������ ��������� ������ this).


?
������� ���:

� define ������� ��� ������� ���� �������� ��������:

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )


������� ���:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;
};

����������� ��� � �������:
typedef struct tagUNIT_COW UNIT_COW;
struct tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  PRIM Cow;
};

!!! ������� �������� ������ ������ ���������� �� ���� �������, � ��� ��� � ������ ������� - ���������� ��� UNIT - �� ��� ����� ���������� Init, Close, Response � Render

��������� ������� ���������� ������� ��������:

VOID AnimUnitAdd( UNIT *Uni )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Units[NumOfUnits++] = Uni, Uni->Init(Uni, &Anim);
}

����� � WinMain:

  . . .
  AnimUnitAdd(UnitCowCreate());
  . . .


���������� ��������� �������� ��������:
UNIT.C:
-- ������� ��������� �� ��������� (UnitInit, UnitClose, UnitResponse, UnitRender)
   (������� - "��������") - ����� ��� ��������� ������������� ������ ������� ��������

?
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sk5UNIT *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitInit( sk5UNIT *Uni, sk5ANIM *Ani )
{
} /* End of 'SK5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sk5UNIT *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitClose( sk5UNIT *Uni, sk5ANIM *Ani )
{
} /* End of 'SK5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sk5UNIT *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitResponse( sk5UNIT *Uni, sk5ANIM *Ani );
{
} /* End of 'SK5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       sk5UNIT *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitRender( sk5UNIT *Uni, sk5ANIM *Ani )
{
} /* End of 'SK5_UnitRender' function */

-- ������� �������� �������:

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (sk5UNIT *) pointer to created unit.
 */
sk5UNIT * SK5_AnimUnitCreate( INT Size )
{
  sk5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(sk5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = SK5_UnitInit;
  Uni->Close = SK5_UnitClose;
  Uni->Response = SK5_UnitResponse;
  Uni->Render = SK5_UnitRender;
  return Uni;
} /* End of 'SK5_AnimUnitCreate' function */

-- ������ ������ ������� ��������:

U_BBALL.C

#include "anim.h"

typedef struct
{
  SK5_UNIT_BASE_FIELDS;
  VEC Pos;
} vg4UNIT_BALL;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitInit( vg4UNIT_BALL *Uni, sk5ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} /* End of 'SK5_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitResponse( vg4UNIT_BALL *Uni, sk5ANIM *Ani );
{
  Uni->Pos += Ani->DeltaTime * 2.4;
} /* End of 'SK5_UnitResponse' function */
/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       sk5ANIM *Ani;
 * RETURNS: None.
 */
static VOID SK5_UnitRender( vg4UNIT_BALL *Uni, sk5ANIM *Ani )
{
  DrawSphere(Uni->Pos, 3);
} /* End of 'SK5_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (sk5UNIT *) pointer to created unit.
 */
sk5UNIT * SK5_UnitCreateBall( VOID )
{
  vg4UNIT_BALL *Uni;

  if ((Uni = (vg4UNIT_BALL *)SK5_AnimUnitCreate(sizeof(vg4UNIT_BALL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)SK5_UnitInit;
  Uni->Response = (VOID *)SK5_UnitResponse;
  Uni->Render = (VOID *)SK5_UnitRender;
} /* End of 'SK5_UnitCreateBall' function */

����������:

DEF.H
  MemHandle
  UINT64 INT64           --> unsigned __int64, __int64
  (DBL FLT --> MTH.H)

MAIN.C - WinMain + WinFunc (������ � WinAPI) + FlipFullScreen

ANIM.C
  SK5_Anim***
  SK5_AnimInit( HWND hWnd );
  SK5_AnimClose( VOID );
  SK5_AnimResize( INT W, INT H );
  SK5_AnimCopyFrame( HDC hDC );
  SK5_AnimRender( VOID );
  SK5_AnimAddUnit( sk5UNIT *Uni );
+ SK5_Anim - ���������� ���������� - ��������� ��������� �������� ���� sk5ANIM:


typedef struct tagvg4UNIT sk5UNIT;
typedef struct tagvg4ANIM
{
  HWND hWnd;                     - ����
  HDC hDC;                       - �������� � ������
  INT W, H;                      - ������ ����

  sk5UNIT *Units[SK5_MAX_UNITS]; - ������ �������� ��������
  INT NumOfUnits;                - ������� ���������� �������� ��������

  + ��� ���������������� ������ �� ������� � ������� �����

} sk5ANIM;

ANIM.H
  -- ����:
  sk5UNIT
  sk5ANIM
  -- ��������� �������
  ***

UNITS.H
-- �������-������������ ��������:
/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (sk5UNIT *) pointer to created unit.
 */

sk5UNIT * SK5_UnitCreateBall( VOID );
. . .

  MAIN.C
#include "units.h"
WinMain:
  . . .
  SK5_AnimUnitAdd(SK5_UnitCreateBall());
  . . .

�������������, ��������, � ��������������� ������� � ������:
VOID SK5_AnimClose( VOID )
{
  for (i = 0; i < SK5_Anim.NumOfUnits; i++)
  {
    SK5_Anim.Units[i]->Close(SK5_Anim.Units[i], &SK5_Anim);
    free(SK5_Anim.Units[i]);
  }
  SK5_Anim.NumOfUnits = 0;
  SK5_RndClose();
}

VOID SK5_AnimRender( VOID )
{
  . . . timer, keyboard, mouse, joystick . . .

  for (i = 0; i < SK5_Anim.NumOfUnits; i++)
    SK5_Anim.Units[i]->Response(SK5_Anim.Units[i], &SK5_Anim);

  SK5_RndStart();
  for (i = 0; i < SK5_Anim.NumOfUnits; i++)
    SK5_Anim.Units[i]->Render(SK5_Anim.Units[i], &SK5_Anim);
  SK5_RndEnd();
}

-= 08.01.2019 =-

Win
Rnd
Anim:
  struct sk5ANIM + SK5_Anim, sk5UNIT
  Anim***
  Integration into Win

+:
\Source Files
  . . .
  \Animation System
    * UNITS.H
  . . .
  \Unit Smples
    \Unit Cow
      * U_COW.C
    \Unit Control
      * U_CTRL.C


Timer
������ � ����������, ����������� ��� ����������� ������������� �� �������. ����������� ������ �� ������� � ����� ������ ������� (Total Time) � ����������� ��������� �������� (Delta Time).

Old style: (������������ ������� �� ����������� �����������)

  #include <time.h>
  clock() -> tick -> CLOCKS_PER_SEC

�� ������ ���������:
  StartTime = clock();
  . . .
�� ������ ����:
  long t = clock();

  GlobalTimeInSec = (t - StartTime) / (DBL)CLOCKS_PER_SEC;

High resolution timer: (������� � �������� �������� ����������)

  static UINT64
    StartTime,  /* Start program time */
    TimePerSec; /* Timer resolution */

�� ������ ���������:
  LARGE_INTEGER t;

���������� �������� ������� (���� � �������)
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
���������� ����� ������
  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

�� ������ ����:
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  GlobalTimeInSec = (DBL)(t.QuadPart - StartTime) / TimePerSec;


��� �����������:
-- ����� ������ ���������
     StartTime
-- ����� ����� ������ - global time
     t - StartTime
-- ����������� �������� ������� (��� ����� �����) - global delta time
     t � OldTime    (OldTime � ����� �������� �����)
-- pause flag:
     IsPause
-- ��������� ����� (� ������ �����) - local time
     t � PauseTime - StartTime
-- ����������� �������� � ������ ����� - local delta time
     == global delta time  ���� !IsPause
     == 0                  ���� IsPause
��� ���������� PauseTime:
  ���� IsPause:
    PauseTime += t - OldTime
-- ��� ����������� ���������� ������ � ������� - frames per second (FPS):
     1 time per second:
       FrameCounter � ������� ������     OldTimeFPS   � ����� �������� ������ FPS
����������
TIMER:
-- "����������" (���������������) ������:
  static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */
-- ������ ��� ������������ (� ��������� ANIM ��� ������� �� �������� ��������):
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
�������:
TimerInit:        <-- AnimInit
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  IsPause = FALSE;
  FPS = 30.0;
  PauseTime = 0;

TimerResponse:    <-- AnimRender
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart � OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart � PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart � OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart � OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;                                  ANIM\TIMER.C
Input system (������� �����)

Keyboard (����������) 

����������� ����!!!

  BYTE Keys[256];      -- ��������� ������ �� ������� �����
  BYTE KeysOld[256];   -- ��������� ������ �� ������� �����
  BYTE KeysClick[256]; -- �������� ������������ ������� ������

��������� �������� ��������� ���������� (� ������ ����)
  GetKeyboardState(Keys);

Keys[i] � ������� ��� 1, ���� i-� ������ ������

������� ���������:
  GetKeyboardState(Keys);
  for (i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    KeysClick[i] = Keys[i] && !KeysOld[i];   <- ������������ ������������ �������
  }
  memcpy(KeysOld, Keys, 256);

������ � ������� Keys[...]:
����������� ������� (����������� �� windows.h):

VK_ESCAPE VK_INSERT VK_LEFT VK_NEXT VK_F1 ... VK_LBUTTON VK_RBUTTON VK_MBUTTON
                                                      (����)
������� �������:
'A', 'B' ... 'Z', '0', '1', ... , '9'

������ ������������� � �������� Loc � ������ �� ������� (������-�����):

UnitResponse:
  /* Uni->CamLoc += Uni->CamDir * Speed * dt */
  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->DeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));

?
Mouse (����) 

���������������� ����������

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

��������� X � Y:

  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  /* ���������� ��������� �� ������ */
  Mdx = pt.x - Mx;
  Mdy = pt.y - My;
  /* ���������� �������� */
  Mx = pt.x;
  My = pt.y;

������ - buttons - � ��������� ���������� (�� Keys/KeysClick)

����� ������ (mouse wheel)

���������� ����������:
INT SK5_MouseWheel;

case WM_MOUSEWHEEL:
  SK5_MouseWheel += (SHORT)HIWORD(wParam);
  return 0;

��������� Z:
  Mdz = SK5_MouseWheel;
  Mz += SK5_MouseWheel;
  SK5_MouseWheel = 0;

������ ������������� � �������� Loc � ������ ������������ Y:

UnitResponse:
  /* Uni->CamLoc ->rotateY(Mx * DeltaTime * AngleSpeed)*/
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->DeltaTime * Uni->AngleSpeed * Ani->Mdx));




?



Joystick (��������)






-- ���������� �������������� ���������� - windows multimedia library:
#include <mmsystem.h> (����� windows.h)  -- ���� ����������

+ ���������� ����������: /* winmm.lib */ ��� � �����, ��� � ����� (������ VS):
#pragma comment(lib, "winmm")

���������������� ����������

  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                        /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                /* Joystick axes */

�����:
  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          JBut[i] = (ji.dwButtons >> i) & 1;
          JButClick[i] = JBut[i] && !JButOld[i];
          JButOld[i] = JBut[i];
        }

        /* Axes */
        JX = SK5_GET_JOYSTIC_AXIS(X);
        JY = SK5_GET_JOYSTIC_AXIS(Y);
        JZ = SK5_GET_JOYSTIC_AXIS(Z);
        JR = SK5_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
!!!
��� � ���������� ��������:
  jc:	
    jc.wXmin jc.wXmax ... Y ... Z ... R ... U
  ji:
    ji.dwXpos ... Y ...

����� ������� (��� X):
   2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin) - 1

����� ������ ��� ���� ����:

#define SK5_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos � jc.w ## A ## min) / (jc.w ## A ## max � jc.w ## A ## min) - 1)

\ANIM\INPUT.C --> SK5_AnimKeyboardResponse();
                  SK5_AnimMouseResponse();
                  SK5_AnimJoystickResponse();
