
#include "libprototype.h"

obj* o;

void start() {
	o = new();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);
}

void end() {
	printf("%s %ld %f\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"));
}
