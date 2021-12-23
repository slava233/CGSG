/* FILE NAME: DEF.H
 * PROGRAMMER: SK3
 * DATE: 23.01.2019
 * PURPOSE: STANDART DECLARARTION
 */

#ifndef __DEF_H_
#define __DEF_H_

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

#include "mth.h"

typedef unsigned __int64 UINT64;

#endif /* __DEF_H_ */

/* END OF 'DEF.H' FILE */

