/* Kononov Svyatoslav 9-3 07.12.2018 */

typedef struct tagLIST LIST;
struct tagLIST
{
  int Data;
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

int Push(STACK *S, int NewData);
int Put(QUEUE *Q, int NewData);
int Get(QUEUE *Q);
int Pop(STACK *S);
void DisplayQueue(QUEUE *Q);
void DisplayStack(STACK *S);
void ClearQueue(QUEUE *Q);
void ClearStack(STACK *S);

/* End of QUST.H file */