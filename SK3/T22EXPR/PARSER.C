/* Kononov Svyatoslav, 10.12.2018, 09-3 */

#include "expr.h"

STACK Stack1, Stack2;

/* Parser string function */
void Parser( QUEUE *QRes, QUEUE *Q )
{
  TOK T = {0};
  enum
  {
    STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
  } state = STATE_PREFIX;

  while (state != STATE_END)
  {
    if (state <= STATE_SUFFIX)
      if (!Get(Q, &T))
        if (state == STATE_SUFFIX)
          state = STATE_DONE;
        else 
          Error("Unexpected end-of-expression\n");
    switch (state)
    {
    case STATE_PREFIX:
      if (T.Id == TOK_NUM || T.Id == TOK_NAME)
        Push(&Stack1, T), state = STATE_SUFFIX;
      else if (T.Id == TOK_OP && T.Op == '(')
        Push(&Stack2, T);
      else if (T.Id == TOK_OP && T.Op == '-')
      {
        T.Op = '@';
        Push(&Stack2, T);
      }
      else 
        Error("Wait for number or '('\n");
      break;
    case STATE_SUFFIX: 
      if (T.Id == TOK_OP)
      {
        DropOpers(T.Op);
        if (T.Op == ')')
          Error("Missing '('");
        else
          Push(&Stack2, T), state = STATE_PREFIX;
      }
      else
        Error("Wait for operation or ')'\n");
      break;
    case STATE_DONE:
      DropOpers(')');
      if (Stack2.Top != NULL)
        Error("Missing ')'");
      while (Pop(&Stack1, &T))
        Push(&Stack2, T);
      while (Pop(&Stack2, &T))
        Put(QRes, T);
      state = STATE_END;
      break;
    }
  }
} /* End of 'Parser' function */