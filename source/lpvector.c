
#include "lpvector.h"

#define LPVECTOR_INITIAL_SIZE 10

void dealloc(obj* self, va_list* args);
void append(obj* self, va_list* args);
void set_at(obj* self, va_list* args);
obj* at(obj* self, va_list* args);

obj* vector() {
	obj* self = object();
	self->dealloc = dealloc;

	obj** value = calloc(LPVECTOR_INITIAL_SIZE, sizeof(obj*));

	set_p(self, "value", &value, sizeof(obj**));
	set_d(self, "capacity", LPVECTOR_INITIAL_SIZE);
	set_d(self, "count", 0);

	bind(self, "append", append);
	bind(self, "set_at", set_at);
	bind_o(self, "at", at);

	return self;
}

void dealloc(obj* self, va_list* args) {
	obj** vector_value = *((obj***)get_p(self, "value"));

	for (int i = 0; i < get_d(self, "count"); i++) {
		release(vector_value[i]);
	}

	free(vector_value);
}

void append(obj* self, va_list* args) {
	obj* o = va_arg(*args, obj*);
	obj** value = *((obj***)get_p(self, "value"));
	long count = get_d(self, "count");
	long capacity = get_d(self, "capacity");

	if (count == capacity - 1) {
		long resized_capacity = capacity << 1;
		value = realloc(value, resized_capacity * sizeof(obj*));
		assert(value);

		// White out new memory from resizing
		memset(value + capacity, 0, resized_capacity);

		set_p(self, "value", &value, sizeof(obj**));
		set_d(self, "capacity", resized_capacity);
	}

	value[count] = o;

	retain(o);

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
