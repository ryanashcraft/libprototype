
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "hashtable.h"

#include "lpstring.h"
#include "lpvector.h"

#ifndef LIBPROTOTYPE_H_
#define LIBPROTOTYPE_H_

struct _obj;

typedef void* (*vfpointer) (struct _obj*, va_list*);
typedef struct _obj* (*ofpointer) (struct _obj*, va_list*);
typedef long (*dfpointer) (struct _obj*, va_list*);
typedef double (*ffpointer) (struct _obj*, va_list*);

typedef struct _obj {
	hashtable* table;
} obj;

typedef struct _method_o {
	ofpointer function;
} method_o;

typedef struct _method_v {
	vfpointer function;
} method_v;

typedef struct _method_d {
	dfpointer function;
} method_d;

typedef struct _method_f {
	ffpointer function;
} method_f;

obj* object();

obj* clone(obj* subject);

void set_o(obj* o, char* key, obj* value);
obj* get_o(obj* o, char* key);

void set_v(obj* o, char* key, void* value, size_t value_size);
void* get_v(obj* o, char* key);

void set_s(obj* o, char* key, char* value);
char* get_s(obj* o, char* key);

void set_d(obj* o, char* key, long value);
long get_d(obj* o, char* key);

void set_f(obj* o, char* key, double value);
double get_f(obj* o, char* key);

void bind_o(obj* o, char* key, ofpointer function);
void bind_v(obj* o, char* key, vfpointer function);
void bind_d(obj* o, char* key, dfpointer function);
void bind_f(obj* o, char* key, ffpointer function);

obj* call_o(obj* o, char* key, ...);
void* call_v(obj* o, char* key, ...);
long call_d(obj* o, char* key, ...);
double call_f(obj* o, char* key, ...);

#endif
