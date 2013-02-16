
#include "lpstring.h"

char char_at(obj* self, va_list* args);

obj* String(char* value) {
	obj* self = Object();
	set_s(self, "value", value);
	set_d(self, "length", strlen(value));
	bind_c(self, "char at", char_at);

	return self;
}

char char_at(obj* self, va_list* args) {
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
