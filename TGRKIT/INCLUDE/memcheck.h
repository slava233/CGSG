/* Copyright (c) Anton Timofeev, 2014
 * One could include this file to check memory leaks
 * Call 'MC_Stats' to print current leaks summary,
 * Call 'MC_Finish' to erase MC resources at the end of yuor program
 */ 

#ifndef _MEM_CHECK_
#define _MEM_CHECK_

#pragma comment(lib, "memcheck.lib")

/*** Interface ***/
void MC_Stats(void);
void MC_Finish(void);

/*** Implementation ***/
void * MC_Malloc(unsigned size, int line, const char *file);
void MC_Free(void *ptr, int line, const char *file);

#define malloc(size) MC_Malloc(size, __LINE__, __FILE__)
#define free(ptr)    MC_Free(ptr, __LINE__, __FILE__)

#define calloc(ptr)  assert(0 && "[MC]: calloc is not implemented.")
#define realloc(ptr) assert(0 && "[MC]: realloc is not implemented.")

#endif /* _MEM_CHECK_ */
