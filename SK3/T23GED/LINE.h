/* Vashpanov Alexandr, 09-3, 07.12.2018 */
#include <glut.h>
#include <stdlib.h>
#include <commondf.h>
#include <WinDef.h>

#define FRAME_W (1920)
#define FRAME_H (1080)
#define W (1920)
#define H (1080)
#define COLOR 0xFFFFFF

extern DOUBLE Zoom;
extern BYTE Frame[FRAME_H][FRAME_W][3];

typedef struct tagLIST LIST;
struct tagLIST
{
  INT X, Y, L, R;
  LIST *Next;
} *LineList;

VOID PutPixel( INT X, INT Y, INT Color );
VOID PutLine( INT X1, INT Y1, INT X2, INT Y2, INT Color );

VOID FillFlood( INT X, INT Y, DWORD Color );

/* END OF 'GEDIT.H' FILE */


