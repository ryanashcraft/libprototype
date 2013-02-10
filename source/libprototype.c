
#include "libprototype.h"

void start();
void end();

method* new_method(fpointer function);

obj* new() {
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

void bind(obj* o, char* key, fpointer function) {
	method* m = new_method(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(void*));
}

void* call(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method* m = ht_get(o->table, key, strlen(key));
	return m->function(&argp);
}

void set_s(obj* o, char* key, char* value) {
	ht_insert(&o->table, key, strlen(key) + 1, value, strlen(value) + 1);
}

char* get_s(obj* o, char* key) {
	return ht_get(o->table, key, strlen(key));
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

method* new_method(fpointer function) {
	method* m = malloc(sizeof(struct _method));
	assert(m);

	m->function = function;

	return m;
}

int main() {
	start();
	atexit(end);
}
