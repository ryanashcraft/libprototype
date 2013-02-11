
#include "libprototype.h"

void start();
void end();

method* new_method(fpointer function);
method_o* new_method_o(fpointer_o function);
method_p* new_method_p(fpointer_p function);
method_d* new_method_d(fpointer_d function);
method_f* new_method_f(fpointer_f function);

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

void bind(obj* o, char* key, fpointer function) {
	method* m = new_method(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method));
	free(m);
}

void bind_o(obj* o, char* key, fpointer_o function) {
	method_o* m = new_method_o(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_o));
	free(m);
}

void bind_p(obj* o, char* key, fpointer_p function) {
	method_p* m = new_method_p(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_p));
	free(m);
}

void bind_d(obj* o, char* key, fpointer_d function) {
	method_d* m = new_method_d(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_d));
	free(m);
}

void bind_f(obj* o, char* key, fpointer_f function) {
	method_f* m = new_method_f(function);
	ht_insert(&o->table, key, strlen(key), m, sizeof(method_f));
	free(m);
}

void call(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	if (o == NULL) {
		fprintf(stderr, "Attempt to call %s on NULL", key);
		abort();
	}

	method* m = ht_get(o->table, key, strlen(key));

	if (m == NULL || m->function == NULL) {
		fprintf(stderr, "Object does not respond to call %s", key);
		abort();
	}

	m->function(o, &argp);
}

obj* call_o(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	if (o == NULL) {
		fprintf(stderr, "Attempt to call %s on NULL", key);
		abort();
	}

	method_o* m = ht_get(o->table, key, strlen(key));

	if (m == NULL || m->function == NULL) {
		fprintf(stderr, "Object does not respond to call %s", key);
		abort();
	}

	return m->function(o, &argp);
}

void* call_p(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	method_p* m = ht_get(o->table, key, strlen(key));

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

void set_p(obj* o, char* key, void* value, size_t value_size) {
	ht_insert(&o->table, key, strlen(key) + 1, value, value_size);
}

void* get_p(obj* o, char* key) {
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

method* new_method(fpointer function) {
	method* m = malloc(sizeof(struct _method));
	assert(m);

	m->function = function;

	return m;
}

method_o* new_method_o(fpointer_o function) {
	method_o* m = malloc(sizeof(struct _method_o));
	assert(m);

	m->function = function;

	return m;
}

method_p* new_method_p(fpointer_p function) {
	method_p* m = malloc(sizeof(struct _method_p));
	assert(m);

	m->function = function;

	return m;
}

method_d* new_method_d(fpointer_d function) {
	method_d* m = malloc(sizeof(struct _method_d));
	assert(m);

	m->function = function;

	return m;
}

method_f* new_method_f(fpointer_f function) {
	method_f* m = malloc(sizeof(struct _method_f));
	assert(m);

	m->function = function;

	return m;
}

int main() {
	start();
	atexit(end);
}
