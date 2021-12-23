практика Ц T36ANIM:
Project:
\Source Files
  \Math Support
    * MTH.H
  \Animation System
    \Rendering System
      * RND.H       --> Rendering system depended
      * RND.C
      * RNDPRIM.C
    * ANIM.H        --> Main declaration module
    * ANIM.C        --> Empty
    * TIMER.H       --> Timer declaration
    * TIMER.C       --> Timer implementation
  \Windows Depended
    * MAIN.C        --> WinMain, MainWinFunc
  * DEF.H           --> mem.leaks detect, incl."mth.h", + later (base types...)
=========================

***.h <-- 


Up to: 20:50
MainWinFunc -> WM_CREATE, WM_SIZE, WM_ERASEBKGND, WM_PAINT, WM_TIMER, WM_DESTROY,
               WM_GETMINMAXINFO
(all is empty + SetTimer/KillTimer)
WinMain -> class reg, win create, full main loop

—оглашени€ об именах:

»спользуем префикс '»‘ ' в начале всех глобальных имен.
(SK5_)

функции & глобальные переменные (!не математику!)
  SK5_FunctionName

константы
  SK5_CONSTANT_NAME

типы (агрегатные)
  vg4TYPE_NAME

SK5_SystemSubsystemVerb -> SK5_AnimTimerInit
                           SK5_AnimFlipFullScreen
                           SK5_RndPrimDraw

17.Rendering System (in 3D)

Rendering pipeline (конвейер вывода)

primitive(V:{x,y,z},I:{#0,#1,#2}) ->
  -> triangle sampling {triangles (P012)} ->
    -> vertex transform to NDC {Pi} * WorldCSmatrix * ViewCSmatrix * Projectionmatrix ->
      -> map to screen (viewport transform) ->
        -> rasterize triangles

ѕлан реализации

- ƒвойна€ буферизаци€

данные:
HWND SK5_hRndWnd;
HDC SK5_hRndDCFrame;
HBITMAP SK5_hRndBmFrame;
INT SK5_RndFrameW, SK5_RndFrameH;

функционал:
VOID SK5_RndInit( HWND hWnd );
VOID SK5_RndClose( VOID );
VOID SK5_RndResize( INT W, INT H )
{
  HDC hDC;

  if (SK5_hRndBmFrame)
    DeleteObject(SK5_hRndBmFrame);

  hDC = GetDC(SK5_hRndWnd);
  SK5_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(SK5_hRndWnd, hDC);
  SelectObject(SK5_hRndDCFrame, SK5_hRndBmFrame);

  SK5_RndFrameW = W;
  SK5_RndFrameH = H;
  SK5_RndProjSet();
}
VOID SK5_RndCopyFrame( HDC hDC );

- –ендеринг

VOID SK5_RndStart( VOID );
VOID SK5_RndEnd( VOID );

-  амера (+проецирование)  RND.C

данные:
DBL
  SK5_RndProjSize = 0.1,  /* Project plane fit square */
  SK5_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  SK5_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  SK5_RndMatrView, /* View coordinate system matrix */
  SK5_RndMatrProj, /* Projection coordinate system matrix */
  SK5_RndMatrVP;   /* Stored (View * Proj) matrix */

функционал:

VOID SK5_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = SK5_RndProjSize / 2;
  if (SK5_RndFrameW > SK5_RndFrameH) 
    ratio_x *= (DBL)SK5_RndFrameW / SK5_RndFrameH;
  else
    ratio_y *= (DBL)SK5_RndFrameH / SK5_RndFrameW;

  SK5_RndMatrProj =
    MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
      SK5_RndProjDist, SK5_RndProjFarClip);
  SK5_RndMatrVP = MatrMulMatr(SK5_RndMatrView, SK5_RndMatrProj);
}
VOID SK5_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  SK5_RndMatrView = MatrView(Loc, At, Up1);
  SK5_RndMatrVP = MatrMulMatr(SK5_RndMatrView, SK5_RndMatrProj);
}

использование:
VOID ...Draw( sk5PRIM *Prim, MATR World  )
{
  MATR M = MatrMulMatr(World, SK5_RndMatrVP);
  . . .
    VEC p = VecMulMatr4x4(Prim->V[i], M);
  . . .
    Proj[i].x = (p.X + 1) * SK5_RndFrameW / 2;
    Proj[i].y = (-p.Y + 1) * SK5_RndFrameH / 2;
  . . .

}

ѕроверка:
»нтеграци€ RENDER в проект WinAPI:

WinMain:
  создание класса окна
  создание окна
  цикл сообщений


WinFunc:
  WM_MINMAXINFO:
    ...
  WM_CREATE:
    SK5_RndInit(hWnd);
    ...
  WM_SIZE:
    SK5_RndResize(LOWORD(lParam), HIWORD(lParam));
    ...
  WM_TIMER:
    SK5_RndStart();
    отрисовка сцены (тестова€)
    SK5_RndEnd();
    InvalidateRect(hWnd, NULL, FALSE);
    ...
  WM_ERASEBKGND:
    return 1;
  WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    SK5_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  WM_DESTROY:
    SK5_RndClose();
    ...

      RNDDATA.C Ц все глобальные переменные
      RNDBASE.C Ц функции базового набора (камера и двойна€ буферизаци€)
      RNDPRIM.C - примитивы
      RND.H     - все объ€влени€ (типы, ссылки на глобальные переменные,
                  прототипы)

                                                                                                                                                                                                                     ѕримитивы                RNDPRIM.C


  - представление данных












будем оспользовать топологию TriMesh Ц сетка треугольников:
  * массив вершин:
      vg4VERTEX *V;       - массив параметров каждой вершины
      INT NumOfV;
  * массив троек индексов вершин дл€ каждого треугольника:
      INT *I;             - будем группировать по 3
      INT NumOfI;

тип представлени€ параметров каждой вершины:
typedef struct tagvg4VERTEX
{
  VEC P;  /* Vertex position */
} vg4VERTEX;

тип представлени€ примитива:
typedef struct tagsk5PRIM
{
  vg4VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
  INT *I;       /* Index array (for trimesh Ц by 3 ones) */
  INT NumOfI;   /* Number of indices */
  MATR Trans;   /* Additional transformation matrix */
} sk5PRIM;

функционал:

SK5_RndPrim***
  BOOL Create( sk5PRIM *Pr, INT NoofV, INT NoofI );
  VOID Free( sk5PRIM *Pr );
  VOID Draw( sk5PRIM *Pr, MATR World );
  BOOL Load( sk5PRIM *Pr, CHAR *FileName );

#include <string.h>
#include <stdlib.h> -- def.h












BOOL SK5_RndPrimCreate( sk5PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(sk5PRIM));

  /* Calculate memory size for primitive data */
  size = sizeof(vg4VERTEX) * NoofV + sizeof(INT) * NoofI;

  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;

  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);

  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);

  /* Store data sizes */
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'SK5_RndPrimCreate' function */

VOID SK5_RndPrimFree( sk5PRIM *Pr ) 
{
  if (Pr->V != NULL)
    free(Pr->V);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(sk5PRIM));
}

VOID SK5_RndPrimDraw( sk5PRIM *Pr, MATR World ) 
{
  INT i;
  POINT *pnts; /* vertex projections */
  MATR M = MatrMulMatr3(Pr->Trans, World, SK5_RndMatrVP);

  /* Allocate memory for projections */
  pnts = malloc(sizeof(POINT) * Pr->NumOfV);
  if (pnts == NULL)
    return;

  /* Project all vertices */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    /* Convert from World to NDC */
    VEC p = VecMulMatr(Pr->V[i].P, M);

    /* Convert NDC to frame (viewport) */
    pnts[i].x = (p.X + 1) * SK5_RndFrameW / 2;
    pnts [i].y = (-p.Y + 1) * SK5_RndFrameH / 2;
  }
  /* Draw all triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    POINT p[3];

    p[0] = pnts[Pr->I[i]];
    p[1] = pnts[Pr->I[i + 1]];
    p[2] = pnts[Pr->I[i + 2]];
    Polygon(SK5_hRndDCFrame, p, 3);
  }
  free(pnts);
} /* End of 'SK5_RndPrimDraw' function */

BOOL SK5_RndPrimLoad( sk5PRIM *Pr, CHAR *FileName ) 
{
  INT nv, ni;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(sk5PRIM));

  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      ni += 3;

  /* Create primitive */
  if (!SK5_RndPrimCreate(Pr, nv, ni))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive data */
  rewind(F);
  nv = ni = 0;
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%f%f%F", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);

      Pr->I[ni++] = n1 - 1;
      Pr->I[ni++] = n2 - 1;
      Pr->I[ni++] = n3 - 1;
    }


  fclose(F);
  return TRUE;
}


