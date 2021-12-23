/* Kononov Svyat 9-3 19.11.2018 */

#include <commondf.h>

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
  int Key;
  TREE *Less, *More;
};

int AccessRecTree( TREE **T, int Key );
int AccessNonRecTree( TREE **T, int Key );