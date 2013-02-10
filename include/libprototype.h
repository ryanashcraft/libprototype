
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "hashtable.h"

#ifndef LIBPROTOTYPE_H_
#define LIBPROTOTYPE_H_

typedef void* (*fpointer) (va_list*);
typedef void* (*ifpointer) (va_list*);

typedef struct _obj {
	hashtable* table;
} obj;

typedef struct _method {
	fpointer function;
} method;


obj* new();

obj* clone(obj* subject);

void set_s(obj* o, char* key, char* value);
char* get_s(obj* o, char* key);

void set_d(obj* o, char* key, long value);
long get_d(obj* o, char* key);

void set_f(obj* o, char* key, double value);
double get_f(obj* o, char* key);

void bind(obj* o, char* key, fpointer function);

void* call(obj* o, char* key, ...);

#endif
