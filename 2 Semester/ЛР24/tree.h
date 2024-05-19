#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

#include "symbol.h"



//typedef struct _SN SN;

//struct _TN {
typedef struct SN {
    symbol t;

    struct SN* r;
    struct SN* l;
} TN;

#endif