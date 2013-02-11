
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

#define LOG_CRITICAL(FORMAT, ...) fprintf(stderr, "%s:%d - " FORMAT "\n", __FILE__, __LINE__, ##__VA_ARGS__)

struct _obj;

typedef void (*fpointer) (struct _obj*, va_list*);
typedef void* (*fpointer_p) (struct _obj*, va_list*);
typedef struct _obj* (*fpointer_o) (struct _obj*, va_list*);
typedef long (*fpointer_d) (struct _obj*, va_list*);
typedef double (*fpointer_f) (struct _obj*, va_list*);
typedef char (*fpointer_c) (struct _obj*, va_list*);

typedef struct _obj {
	hashtable* table;
	unsigned int retain_count;
	fpointer dealloc;
} obj;

typedef struct _method {
	fpointer function;
} method;

typedef struct _method_o {
	fpointer_o function;
} method_o;

typedef struct _method_p {
	fpointer_p function;
} method_p;

typedef struct _method_d {
	fpointer_d function;
} method_d;

typedef struct _method_f {
	fpointer_f function;
} method_f;

typedef struct _method_c {
	fpointer_c function;
} method_c;

obj* object();
obj* clone(obj* subject);
void retain(obj*);
obj* release(obj*);
obj* delete(obj*);

void set_o(obj* o, char* key, obj* value);
obj* get_o(obj* o, char* key);

void set_p(obj* o, char* key, void* value, size_t value_size);
void* get_p(obj* o, char* key);

void set_s(obj* o, char* key, char* value);
char* get_s(obj* o, char* key);

void set_d(obj* o, char* key, long value);
long get_d(obj* o, char* key);

void set_f(obj* o, char* key, double value);
double get_f(obj* o, char* key);

void set_c(obj* o, char* key, char value);
char get_c(obj* o, char* key);

void bind(obj* o, char* key, fpointer function);
void call(obj* o, char* key, ...);

void bind_o(obj* o, char* key, fpointer_o function);
obj* call_o(obj* o, char* key, ...);

void bind_p(obj* o, char* key, fpointer_p function);
void* call_p(obj* o, char* key, ...);

void bind_d(obj* o, char* key, fpointer_d function);
long call_d(obj* o, char* key, ...);

void bind_f(obj* o, char* key, fpointer_f function);
double call_f(obj* o, char* key, ...);

void bind_c(obj* o, char* key, fpointer_c function);
char call_c(obj* o, char* key, ...);

#endif
