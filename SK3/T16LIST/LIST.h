/* Kononov Svyat 9-3 16.11.2018 */

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

#define MAX 100

typedef struct tagLIST LIST;
struct tagLIST
{
  int Data;
  LIST *Next;
};

int ListAddToFront(LIST **L, int NewData);
void ListDisplay(LIST *L);
void ClearList(LIST **L);
int ListDelFromFront(LIST **L);
int ListAddToBack(LIST **L, int NewData);
int ListDelFromBack(LIST **L);
int Add(DATE **L, char *Name, int D, int M, int Y);
int Del(DATE **L);

/* End of LIST.h file */