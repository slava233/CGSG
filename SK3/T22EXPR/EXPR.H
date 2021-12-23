/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include <commondf.h>

#ifndef NDEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */
#include <stdlib.h>
                                                          
#define MAX 255
#define MAX_NAME 255

typedef enum
{
  TOK_OP,
  TOK_NUM,
  TOK_NAME
} TOKID;

typedef struct
{    
  TOKID Id;
  char Op;
  double Num;
  char Name[MAX_NAME];
} TOK;

typedef struct tagLIST LIST;
struct tagLIST
{
  TOK T;
  LIST *Next;
};

typedef struct tagQUEUE QUEUE;
struct tagQUEUE
{
  LIST *Head, *Tail;
};

typedef struct tagSTACK STACK;
struct tagSTACK
{
  LIST *Top;
};

extern STACK Stack1, Stack2, StackEval;

void Error( char *Str, ... );
double Eval( QUEUE *Q );
void Push( STACK *S, TOK T );
void Put( QUEUE *Q, TOK T );
BOOL Get( QUEUE *Q, TOK *T );
BOOL Pop( STACK *S, TOK *T );
int Scanner( QUEUE *Q, char *S );
void DisplayQueue( QUEUE *Q );
void DisplayStack( STACK *S );
void ClearQueue( QUEUE *Q );
void ClearStack( STACK *S );
void Parser( QUEUE *QRes, QUEUE *Q );
void PrintTok( TOK T );
void SetValue( char *Name, double Value );
void DisplayVarTable( void );
double GetValue( char *Name );
void ClearVarTable( void );
int CheckAssoc( char Op1, char Op2 );