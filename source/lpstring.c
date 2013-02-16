
#include "lpstring.h"

char charat(obj* self, va_list* args);

obj* string(char* value) {
	obj* self = object();
	set_s(self, "value", value);
	set_d(self, "length", strlen(value));
	bind_c(self, "charat", charat);

	return self;
}

char charat(obj* self, va_list* args) {
	int i = va_arg(*args, int);

	if (i < 0) {
		LOG_CRITICAL("Attempt to access index %d of string with length %d", i, get_d(self, "length"));
		abort();
	} else if (i >= get_d(self, "length")) {
		LOG_CRITICAL("Attempt to access index %d of string with length %d", i, get_d(self, "length"));
		abort();
	}

	return get_s(self, "value")[i];
}
