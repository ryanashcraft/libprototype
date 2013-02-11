
#include "lpvector.h"

#define LPVECTOR_INITIAL_SIZE 10

void append(obj* o, va_list* args);
void set_at(obj* o, va_list* args);
obj* at(obj* o, va_list* args);

obj* vector() {
	obj* self = object();

	obj** value = calloc(LPVECTOR_INITIAL_SIZE, sizeof(obj*));
	set_p(self, "value", &value, sizeof(obj**));
	set_d(self, "count", 0);

	bind(self, "append", append);
	bind(self, "set_at", set_at);
	bind_o(self, "at", at);

	return self;
}

void append(obj* self, va_list* args) {
	obj* o = va_arg(*args, obj*);
	obj** vector_value = *((obj***)get_p(self, "value"));
	long count = get_d(self, "count");
	vector_value[count] = o;

	set_d(self, "count", count + 1);
}

void set_at(obj* self, va_list* args) {
	long i = va_arg(*args, long);

	if (i < 0) {
		LOG_CRITICAL("Attempt to access index %ld of vector with count %ld", i, get_d(self, "count"));
		abort();
	} else if (i >= get_d(self, "count")) {
		LOG_CRITICAL("Attempt to access index %ld of vector with count %ld", i, get_d(self, "count"));
		abort();
	}

	obj* o = va_arg(*args, obj*);
	obj** vector_value = *((obj***)get_p(self, "value"));
	vector_value[i] = o;

	set_d(self, "count", get_d(self, "count") + 1);
}

obj* at(obj* self, va_list* args) {
	long i = va_arg(*args, long);

	if (i < 0) {
		LOG_CRITICAL("Attempt to access index %ld of vector with count %ld", i, get_d(self, "count"));
		abort();
	} else if (i >= get_d(self, "count")) {
		LOG_CRITICAL("Attempt to access index %ld of vector with count %ld", i, get_d(self, "count"));
		abort();
	}

	obj** vector_value = *((obj***)get_p(self, "value"));
	obj* o = vector_value[i];
	return o;
}
