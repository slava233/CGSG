#define MAX 200
#define MAX_ENEMIES 3
#define INFINITY 255

typedef unsigned char BYTE;
typedef double DBL;
typedef struct tegENEMY
{
  int X, Y;
  BYTE Solution[MAX][MAX];
  DBL DeltaTime;
} ENEMY;

extern DBL DeltaTime;

extern ENEMY Enemies[MAX_ENEMIES];
extern BYTE Lab[MAX][MAX];
extern BYTE AvaX, AvaY;
extern int GAME_OVER;

void PutPixel( int X, int Y, int Color );

void LabLoad( char *FileName );
void DrawPlace( void );
void BrainEnemies( void );  