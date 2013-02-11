
#include "lpstring.h"

char charat(obj* self, va_list* args);

obj* string(char* value) {
	obj* self = object();
	set_s(self, "value", value);
	set_d(self, "length", strlen(value));
	bind_c(self, "charat", charat);

	return self;
}

obj* formatted_string(char* format, ...) {
	va_list args;
	va_start(args, format);

	int size_needed = vsnprintf(NULL, 0, format, args);
	char* value = calloc(size_needed + 1, sizeof(char));
	vsnprintf(value, size_needed, format, args);

	obj* self = object();
	set_s(self, "value", value);
	free(value);

	set_d(self, "length", size_needed - 1);
	bind_c(self, "charat", charat);

	return self;
}

char charat(obj* self, va_list* args) {
	long i = va_arg(*args, long);

	if (i < 0) {
		LOG_CRITICAL("Attempt to access index %ld of string with length %ld", i, get_d(self, "length"));
		abort();
	} else if (i >= get_d(self, "length")) {
		LOG_CRITICAL("Attempt to access index %ld of string with length %ld", i, get_d(self, "length"));
		abort();
	}

	return get_s(self, "value")[i];
}
