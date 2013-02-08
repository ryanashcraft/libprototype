
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "rtc.h"

method* new_method(fpointer function);

obj* new_obj() {
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

void set_s(obj* o, char* key, char* value) {
	ht_insert(&o->table, key, strlen(key), value, strlen(value));
}

char* get_s(obj* o, char* key) {
	return ht_get(o->table, key, strlen(key));
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

method* new_method(fpointer function) {
	method* m = malloc(sizeof(struct _method));
	assert(m);

	m->function = function;

	return m;
}

void* test_func(va_list* args) {
	return va_arg(*args, char*);
}

void* test_func2(va_list* args) {
	return va_arg(*args, int*);
}

int main() {
	obj* o = new_obj();

	set_s(o, "foo", "fighter");
	char* s = get_s(o, "foo");
	printf("%s\n", s);

	bind(o, "test", test_func);
	s = call(o, "test", "param1");
	printf("%s\n", s);

	obj* o2 = clone(o);
	set_s(o2, "foo", "not a fighter");
	s = get_s(o2, "foo");
	printf("%s\n", s);

	bind(o2, "test2", test_func2);
	int i = (int)call(o2, "test2", 5);
	printf("%d\n", i);
}
