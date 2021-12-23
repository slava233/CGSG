typedef unsigned char byte;
typedef double DBL;

typedef struct
{
  DBL Re, Im;
} COMPL;

extern DBL SyncTime;

COMPL ComplSet( DBL A, DBL B );
COMPL ComplAddCompl( COMPL A, COMPL B );
COMPL ComplMultCompl( COMPL A, COMPL B );
DBL ComplNorm2( COMPL Z );
int Mandelbrot( COMPL Z );
int Julia( COMPL Z, COMPL C );
void PutMandl( void );

void PutPixel( int X, int Y, int Color );