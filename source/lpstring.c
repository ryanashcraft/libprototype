
#include "lpstring.h"

static char charat(obj* self, va_list* args);
static void append(obj* self, va_list* args);

obj* string(char* value) {
	obj* self = object();
	set_s(self, "value", value);
	set_d(self, "length", strlen(value) + 1);
	set_d(self, "capacity", strlen(value) + 1);

	bind_c(self, "charat", charat);
	bind(self, "append", append);

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
	set_d(self, "capacity", size_needed);

	bind_c(self, "charat", charat);
	bind(self, "append", append);

	return self;
}

void append(obj* self, va_list* args) {
	char* part_two = va_arg(*args, char*);
	char* part_one = get_s(self, "value");
	char* joined;

	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);
	long capacity = get_d(self, "capacity");

	if (part_one_length + part_two_length + 1 > capacity) {
		long new_capacity = (capacity * 2) + part_two_length + 1;
		joined = calloc(new_capacity, sizeof(char));
		assert(joined);
		strncpy(joined, part_one, part_one_length);
		set_d(self, "capacity", new_capacity);
	}
 	
	strncat(joined, part_two, part_two_length);
	set_s(self, "value", joined);

	set_d(self, "length", part_one_length + part_two_length);

	free(joined);
}

static char charat(obj* self, va_list* args) {
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
