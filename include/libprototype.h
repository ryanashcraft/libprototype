
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "hashtable.h"

#include "lpstring.h"

#ifndef LIBPROTOTYPE_H_
#define LIBPROTOTYPE_H_

struct _obj;

typedef void* (*fpointer) (struct _obj*, va_list*);
typedef long (*dfpointer) (struct _obj*, va_list*);
typedef double (*ffpointer) (struct _obj*, va_list*);

typedef struct _obj {
	hashtable* table;
} obj;

typedef struct _method {
	fpointer function;
} method;

typedef struct _method_d {
	dfpointer function;
} method_d;

typedef struct _method_f {
	ffpointer function;
} method_f;

obj* object();

obj* clone(obj* subject);

void set_s(obj* o, char* key, char* value);
char* get_s(obj* o, char* key);

void set_d(obj* o, char* key, long value);
long get_d(obj* o, char* key);

void set_f(obj* o, char* key, double value);
double get_f(obj* o, char* key);

void bind(obj* o, char* key, fpointer function);
void bind_d(obj* o, char* key, dfpointer function);
void bind_f(obj* o, char* key, ffpointer function);

void* call(obj* o, char* key, ...);
long call_d(obj* o, char* key, ...);
double call_f(obj* o, char* key, ...);

#endif
