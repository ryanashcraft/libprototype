
#include "libprototype.h"

obj* s;
obj* v;

void start() {
	obj* o = object();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);
	set_c(o, "c", 'A');

	s = string("oh hai der!");

	v = vector(10);
	call(v, "append", o);

	printf("%ld\n", get_d(v, "count"));
}

void end() {
	obj* o = call_o(v, "at", 0);
	
	printf("%s %ld %f %c\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"), get_c(o, "c"));

	printf("%s\n", get_s(s, "value"));

	printf("%c\n", call_c(s, "charat", 5));
}
