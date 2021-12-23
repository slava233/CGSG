typedef struct tegVEC
{
  double X, Y, Z;
} VEC;

typedef unsigned char byte;

extern double Speed, DeltaTime;

#define W 660
#define H 360

void PutPixel(int X, int Y, int Color);

void StarsInit(void);
void StarsMove(void);
void StarsDraw(void);
