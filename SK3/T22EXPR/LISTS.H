/* Vashpanov Alexandr, 09-3, 31.10.2018 */
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
typedef struct 
{
  LIST *Head;
  LIST *Tale;
}QUEUE;
typedef struct 
{
  LIST *Top;
}STACK;
int Put( QUEUE *Q, int NewData );       
int Push( STACK *L, int NewData );
int Pop( STACK *L );
int Get( QUEUE *L );
void ClearStack( STACK *Q );
void DisplayStack( STACK *Q );
void ClearQueue( QUEUE *Q );
void DisplayQueue( QUEUE *Q );
void PrintTok( TOK T );

