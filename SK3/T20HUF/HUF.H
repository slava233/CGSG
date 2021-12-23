/* Debug memory allocation support */
#ifndef NDEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((void)0)
#endif /* _DEBUG */
#include <stdlib.h>

typedef struct tagTREE TREE;
struct tagTREE
{
  char Ch;
  long Freq;
  TREE *Left, *Right;
};

typedef struct
{
  int Code[47], Len;
} CODE;

void Stat( char *FileName );
void BuildCodes( TREE *T );
void CountFreq( FILE *F );
void PlaceNode( char Ch, long Freq, TREE *L, TREE *R );
void DrawTree( TREE *T, int Level );
long Freq[256];
TREE *Nodes[256];
CODE NewCodes[256], CurCode;
int NumOfNodes;
