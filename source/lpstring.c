
#include "lpstring.h"

long length(obj* self, va_list* args);
long charat(obj* self, va_list* args);

obj* string(char* value) {
	obj* self = new();
	set_s(self, "value", value);
	bind_d(self, "length", length);
	bind_d(self, "charat", charat);

	return self;
}

long length(obj* self, va_list* args) {
	return (long)strlen(get_s(self, "value"));
}

long charat(obj* self, va_list* args) {
	long i = va_arg(*args, long);

	if (i < 0)
		return -1;
	else if (i >= call_d(self, "length"))
		return -1;

	return (long)get_s(self, "value")[i];
}
