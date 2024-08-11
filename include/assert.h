#ifdef _ASSERT_H
#define _ASSERT_H

#include <stdlib.h>

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(expr) (expr || abort())
#endif

#endif
