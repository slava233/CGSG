Animation system
OS	Animation	Application	Render3D
WinMain:
- регистрация класса
  окна
- создание окна
- цикл сообщений
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
инициализация

AnimClose();
деинициализация

AnimResize(W, H);
изменение размера кадра

AnimCopyFrame(hDC);
копирование кадра

AnimRender();
построение кадра
(опрос устройств ввода, обновление таймера, опрос всех элементов анимации и вызов у них функции Response, очистка кадра и вызов у всех функций анимации Render)


+контекст анимации
ANIM Anim;
	массив элементов анимации
UNIT:
[

  Init(Anim);
   инициализация

  Close(Anim);
   деинициализация


  Response(Anim);
отклик элемента анимации на смену кадра (обработка клавиатуры, таймера и т.п.)

  Render(Anim);
отрисовка элемента анимации

]

в каждую функцию элемента анимации приходит параметр - Anim - текущий контекст (параметры) анимации:
  - клавиатура
  - мышь
  - джойстик
  - таймер
  - параметры ввода (...)
  - параметры визуализации (hDC, ... )	
RndInit(hWnd);

RndClose();

RndResize(W, H);

RndStart();

RndEnd();

RndCopyFrame(hDC);

-----------

RndPrim:
  Create/Load/Free/Draw


Как сделать элементы анимации с разным поведением?

1.разное поведение - 
  - указатели на функции Init, Close, Response, Render в структуре UNIT

первое приближение:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

т.е. в анимации хранится массив указателей на элементы анимации:

#define MAX_UNITS 3000
UNIT *Units[MAX_UNITS];
INT NumOfUnits;

----------------------
добавление:
UNIT *Uni = UnitCreateCow();

Anim.Units[Anim.NumOfUnits] = Uni;
Uni->Init(Uni, &Anim);
  или
    Anim.Units[Anim.NumOfUnits]->Init(Anim.Units[Anim.NumOfUnits], &Anim);
Anim.NumOfUnits++;

в AnimRender у анимации:

  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Render(Anim.Units[i], &Anim);

!!! Основной принцип ООП: данные управляют собственным поведением !!!

Все написанное выше являет собой реализацию полиморфоного поведения.

Принципы ООП:
- ИНКАПСУЛЯЦИЯ (incapsulation) - сокрытие данных
- НАСЛЕДОВАНИЕ (iheritance) - включение полей одних структур - в другие
- ПОЛИМОРФИЗМ (polymorph, override) - различное поведение наследуемых функций

2.как сделать данные (элементы анимации) разного размера?

Все объекты анимации (UNIT – "юнит") хранятся как указатели в общем массиве.
Так как начало всех объектов анимации содержит одинаковые поля – при доступе к каждому из объектов система будеи иметь возможность вызвать любую функцию из базовых 4-х.
Для доступа из функции к дополнительным значениям – в каждую передается указатель на саму структуру объекта анимации.


UNIT *Units[MAX_UNITS]:





				












!!! Т.е. каждая функция UNIT-а должна еще получать указатель  на самого себя (self-pointer, в Си++ это решено служебным словом this).


?
базовый тип:

в define запишем все базовые поля элемента анимации:

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )


базовый тип:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;
};

производный тип – примеры:
typedef struct tagUNIT_COW UNIT_COW;
struct tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  PRIM Cow;
};

!!! Система анимации хранит массив УКАЗАТЕЛЕЙ на наши объекты, а так как в начале каждого - одинаковый тип UNIT - то она может пользовать Init, Close, Response и Render

Реализуем функцию добавления объекта анимации:

VOID AnimUnitAdd( UNIT *Uni )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Units[NumOfUnits++] = Uni, Uni->Init(Uni, &Anim);
}

Вызов в WinMain:

  . . .
  AnimUnitAdd(UnitCowCreate());
  . . .


Реализация обработки объектов анимации:
UNIT.C:
-- функции обработки по умолчанию (UnitInit, UnitClose, UnitResponse, UnitRender)
   (функции - "заглушки") - нужны для начальной инициализации любого объекта анимации

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

-- функция создания объекта:

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

-- пример своего объекта анимации:

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

РЕАЛИЗАЦИЯ:

DEF.H
  MemHandle
  UINT64 INT64           --> unsigned __int64, __int64
  (DBL FLT --> MTH.H)

MAIN.C - WinMain + WinFunc (работа с WinAPI) + FlipFullScreen

ANIM.C
  SK5_Anim***
  SK5_AnimInit( HWND hWnd );
  SK5_AnimClose( VOID );
  SK5_AnimResize( INT W, INT H );
  SK5_AnimCopyFrame( HDC hDC );
  SK5_AnimRender( VOID );
  SK5_AnimAddUnit( sk5UNIT *Uni );
+ SK5_Anim - глобальная переменная - структура контекста анимации типа sk5ANIM:


typedef struct tagvg4UNIT sk5UNIT;
typedef struct tagvg4ANIM
{
  HWND hWnd;                     - окно
  HDC hDC;                       - контекст в памяти
  INT W, H;                      - размер окна

  sk5UNIT *Units[SK5_MAX_UNITS]; - массив объектов анимации
  INT NumOfUnits;                - текущее количество объектов анимации

  + все пользовательские данные от таймера и системы ввода

} sk5ANIM;

ANIM.H
  -- типы:
  sk5UNIT
  sk5ANIM
  -- прототипы функций
  ***

UNITS.H
-- функции-конструкторы примеров:
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

Использование, например, в деинициализации системы и выводе:
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
Таймер – абстракция, необходимая для организации синхронизации по времени. Необходимые данные от таймера – время работы системы (Total Time) и межкадровая временная задержка (Delta Time).

Old style: (классический вариант со стандартной библиотекой)

  #include <time.h>
  clock() -> tick -> CLOCKS_PER_SEC

на старте программы:
  StartTime = clock();
  . . .
на каждом шаге:
  long t = clock();

  GlobalTimeInSec = (t - StartTime) / (DBL)CLOCKS_PER_SEC;

High resolution timer: (вариант с таймеров высокого разрешения)

  static UINT64
    StartTime,  /* Start program time */
    TimePerSec; /* Timer resolution */

на старте программы:
  LARGE_INTEGER t;

определить точность таймера (тики в секунду)
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
определить время начала
  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

на каждом шаге:
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  GlobalTimeInSec = (DBL)(t.QuadPart - StartTime) / TimePerSec;


Что потребуется:
-- время начала программы
     StartTime
-- общее время работы - global time
     t - StartTime
-- межкадровая задержка времени (без учета паузы) - global delta time
     t – OldTime    (OldTime – время прошлого кадра)
-- pause flag:
     IsPause
-- локальное время (с учетом паузы) - local time
     t – PauseTime - StartTime
-- межкадровая задержка с учетом паузы - local delta time
     == global delta time  если !IsPause
     == 0                  если IsPause
для вычисления PauseTime:
  если IsPause:
    PauseTime += t - OldTime
-- для определения количества кадров в секунду - frames per second (FPS):
     1 time per second:
       FrameCounter – счетчик кадров     OldTimeFPS   – время прошлого замера FPS
Реализация
TIMER:
-- "внутренние" (вспомогательные) данные:
  static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */
-- данные для пользователя (в структуре ANIM для доступа из объектов анимации):
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
Функции:
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
    PauseTime += t.QuadPart – OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart – PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart – OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart – OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;                                  ANIM\TIMER.C
Input system (Система ввода)

Keyboard (клавиатура) 

Асинхронный ввод!!!

  BYTE Keys[256];      -- состояние клавиш на текущем кадре
  BYTE KeysOld[256];   -- состояние клавиш на прошлом кадре
  BYTE KeysClick[256]; -- признаки однократного нажатия клавиш

Получение текущего состояния клавиатуры (и кнопок мыши)
  GetKeyboardState(Keys);

Keys[i] – старший бит 1, если i-я кнопка нажата

Типовая обработка:
  GetKeyboardState(Keys);
  for (i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    KeysClick[i] = Keys[i] && !KeysOld[i];   <- Отслеживание однократного нажатия
  }
  memcpy(KeysOld, Keys, 256);

Номера в массиве Keys[...]:
специальные клавиши (обозначения из windows.h):

VK_ESCAPE VK_INSERT VK_LEFT VK_NEXT VK_F1 ... VK_LBUTTON VK_RBUTTON VK_MBUTTON
                                                      (мыша)
обычные клавиши:
'A', 'B' ... 'Z', '0', '1', ... , '9'

Пример использования – движение Loc у камеры от стрелок (вперед-назад):

UnitResponse:
  /* Uni->CamLoc += Uni->CamDir * Speed * dt */
  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->DeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));

?
Mouse (мышь) 

пользовательские переменные

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

получение X и Y:

  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  /* приращение координат на экране */
  Mdx = pt.x - Mx;
  Mdy = pt.y - My;
  /* абсолютные значения */
  Mx = pt.x;
  My = pt.y;

Кнопки - buttons - в обработке клавиатуры (из Keys/KeysClick)

опрос колеса (mouse wheel)

глобальная переменная:
INT SK5_MouseWheel;

case WM_MOUSEWHEEL:
  SK5_MouseWheel += (SHORT)HIWORD(wParam);
  return 0;

получение Z:
  Mdz = SK5_MouseWheel;
  Mz += SK5_MouseWheel;
  SK5_MouseWheel = 0;

Пример использования – кручение Loc у камеры относительно Y:

UnitResponse:
  /* Uni->CamLoc ->rotateY(Mx * DeltaTime * AngleSpeed)*/
  Uni->CamLoc =
    PointTransform(Uni->CamLoc,
      MatrRotateY(Ani->DeltaTime * Uni->AngleSpeed * Ani->Mdx));




?



Joystick (джойстик)






-- Необходима дополнительная библиотека - windows multimedia library:
#include <mmsystem.h> (после windows.h)  -- файл заголовков

+ подключаем библиотеку: /* winmm.lib */ или в прект, или в тесте (только VS):
#pragma comment(lib, "winmm")

пользовательские переменные

  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                        /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                /* Joystick axes */

опрос:
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
Оси в структурах задаются:
  jc:	
    jc.wXmin jc.wXmax ... Y ... Z ... R ... U
  ji:
    ji.dwXpos ... Y ...

общая формула (для X):
   2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin) - 1

общий макрос для всех осей:

#define SK5_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos – jc.w ## A ## min) / (jc.w ## A ## max – jc.w ## A ## min) - 1)

\ANIM\INPUT.C --> SK5_AnimKeyboardResponse();
                  SK5_AnimMouseResponse();
                  SK5_AnimJoystickResponse();
