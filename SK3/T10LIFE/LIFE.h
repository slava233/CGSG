typedef unsigned char byte;

#define W 800
#define H 600
#define FRAME_W 800
#define FRAME_H 600

void PutPixel( int X, int Y, int Color );
void FieldInit( byte *F );
void DrawField( byte *F );
void NewGeneration( byte *F1, byte *F2 );
int GetCell( byte *F, int x, int y );
void SetCell( byte *F, int X, int Y, int value );
int GetNeighbours( byte *F, int x, int y );
void LifeStep( void );
void LifeInit( void );



