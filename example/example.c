
#include "libprototype.h"

obj* s;
obj* v;

void start() {
	obj* o = Object();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);
	set_c(o, "c", 'A');

	s = String("oh hai der!");

	v = Vector(10);
	call(v, "append", o);
	printf("%d\n", get_d(v, "count"));

	obj* ll = LinkedList();
	call(ll, "push back", s);

	printf("%s\n", get_s(call_o(ll, "back"), "value"));
}

void end() {
	obj* o = call_o(v, "at", 0);
	printf("%s %d %f %c\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"), get_c(o, "c"));
	printf("%c\n", call_c(s, "char at", 5));
	release(o);
}
