
#include "lpstring.h"

long charat(obj* self, va_list* args);

obj* string(char* value) {
	obj* self = object();
	set_s(self, "value", value);
	set_d(self, "length", strlen(value));
	bind_d(self, "charat", charat);

	return self;
}

long charat(obj* self, va_list* args) {
	long i = va_arg(*args, long);

	if (i < 0)
		return -1;
	else if (i >= get_d(self, "length"))
		return -1;

	return (long)get_s(self, "value")[i];
}
