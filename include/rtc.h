
#include "hashtable.h"
#include <stdarg.h>

typedef void* (*fpointer) (va_list*);
typedef void* (*ifpointer) (va_list*);

typedef struct _obj {
	hashtable* table;
} obj;

typedef struct _method {
	fpointer function;
} method;
