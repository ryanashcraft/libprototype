
#include "libprototype.h"

void start();
void end();

method_o* new_method_o(ofpointer function);
method_v* new_method_v(vfpointer function);
method_d* new_method_d(dfpointer function);
method_f* new_method_f(ffpointer function);

obj* object() {
	obj* o = malloc(sizeof(struct _obj));
	assert(o);

	o->table = ht_create(4, 2);

	return o;
}

obj* clone(obj* subject) {
	obj* clone = malloc(sizeof(struct _obj));
	assert(clone);

	memcpy(clone, subject, sizeof(struct _obj));

	return clone;
}

void bind_o(obj* o, char* key, ofpointer function) {
	method_o* m = new_method_o(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_o*));
	free(m);
}

void bind_v(obj* o, char* key, vfpointer function) {
	method_v* m = new_method_v(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_v*));
	free(m);
}

void bind_d(obj* o, char* key, dfpointer function) {
	method_d* m = new_method_d(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_d*));
	free(m);
}

void bind_f(obj* o, char* key, ffpointer function) {
	method_f* m = new_method_f(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_f*));
	free(m);
}

obj* call_o(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method_o* m = ht_get(o->table, key, strlen(key));

	return m->function(o, &argp);
}

void* call_v(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method_v* m = ht_get(o->table, key, strlen(key));

	return m->function(o, &argp);
}

long call_d(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method_d* m = ht_get(o->table, key, strlen(key));

	return m->function(o, &argp);
}

double call_f(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method_f* m = ht_get(o->table, key, strlen(key));

	return m->function(o, &argp);
}

void set_o(obj* o, char* key, obj* value) {
	ht_insert(&o->table, key, strlen(key) + 1, value, sizeof(struct _obj));
}

obj* get_o(obj* o, char* key) {
	return ht_get(o->table, key, strlen(key) + 1);
}

void set_v(obj* o, char* key, void* value, size_t value_size) {
	ht_insert(&o->table, key, strlen(key) + 1, value, value_size);
}

void* get_v(obj* o, char* key) {
	return ht_get(o->table, key, strlen(key) + 1);
}

void set_s(obj* o, char* key, char* value) {
	ht_insert(&o->table, key, strlen(key) + 1, value, strlen(value) + 1);
}

char* get_s(obj* o, char* key) {
	return ht_get(o->table, key, strlen(key) + 1);
}

void set_d(obj* o, char* key, long value) {
	long* valuep = malloc(sizeof(long));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(long));
	free(valuep);
}

long get_d(obj* o, char* key) {
	long* valuep = ht_get(o->table, key, strlen(key));
	return *valuep;
}

void set_f(obj* o, char* key, double value) {
	double* valuep = malloc(sizeof(double));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(double));
	free(valuep);
}

double get_f(obj* o, char* key) {
	double* valuep = ht_get(o->table, key, strlen(key));
	return *valuep;
}

method_o* new_method_o(ofpointer function) {
	method_o* m = malloc(sizeof(struct _method_o));
	assert(m);

	m->function = function;

	return m;
}

method_v* new_method_v(vfpointer function) {
	method_v* m = malloc(sizeof(struct _method_o));
	assert(m);

	m->function = function;

	return m;
}

method_d* new_method_d(dfpointer function) {
	method_d* m = malloc(sizeof(struct _method_d));
	assert(m);

	m->function = function;

	return m;
}

method_f* new_method_f(ffpointer function) {
	method_f* m = malloc(sizeof(struct _method_f));
	assert(m);

	m->function = function;

	return m;
}

int main() {
	start();
	atexit(end);
}
