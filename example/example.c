
#include "libprototype.h"

obj* o;
obj* s;

void start() {
	o = new();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);

	s = string("oh hai der!");
}

void end() {
	printf("%s %ld %f\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"));

	printf("%s\n", get_s(s, "value"));
}
