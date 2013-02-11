
#include "lpvector.h"

void set_at(obj* o, va_list* args);
obj* at(obj* o, va_list* args);

obj* vector(long size) {
	obj* self = object();

	obj** value = calloc(size, sizeof(obj*));
	set_p(self, "value", &value, sizeof(obj**));

	bind(self, "set_at", set_at);
	bind_o(self, "at", at);

	return self;
}

void set_at(obj* self, va_list* args) {
	long i = va_arg(*args, long);
	obj* o = va_arg(*args, obj*);
	obj** vector_value = *((obj***)get_p(self, "value"));
	vector_value[i] = o;
}

obj* at(obj* self, va_list* args) {
	long i = va_arg(*args, long);
	obj** vector_value = *((obj***)get_p(self, "value"));
	obj* o = vector_value[i];
	return o;
}
