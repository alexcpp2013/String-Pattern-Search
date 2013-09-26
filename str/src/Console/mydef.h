
/*-----------------------------------------------------------------------------

Melnyk O. V.
mydef.h

-----------------------------------------------------------------------------*/
#ifndef MYDEF_H
#define MYDEF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/

#define uli unsigned long int
#define textView 150L
#define patternView 150L
#define maxAlf 256 /*UCHAR_MAX*/
#define EOS '\0'

/*---------------------------------------------------------------------------*/

struct _cell
{
	long int element;
    struct _cell *next;
};

typedef struct _cell *List;

struct _graph
{
	long int vertexNumber,
        	 edgeNumber,
        	 vertexCounter,
        	 initial,
        	 *terminal,
        	 *target,
        	 *suffixLink,
        	 *length,
        	 *position,
        	 *shift;
};

typedef struct _graph *Graph;
typedef long int BOOLean;

#define UNDEFINED -1

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
