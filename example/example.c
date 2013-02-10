
#include "libprototype.h"

obj* s;
obj* v;

void start() {
	obj* o = object();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);

	s = string("oh hai der!");

	v = vector(10);
	call_o(v, "set_at", 1, o);
}

void end() {
	obj* o = call_o(v, "at", 1);
	
	printf("%s %ld %f\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"));

	printf("%s\n", get_s(s, "value"));

	printf("%c\n", (char)call_d(s, "charat", 5));
}
