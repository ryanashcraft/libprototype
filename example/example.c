
#include "libprototype.h"

obj* s;
obj* v;

void start() {
	obj* o = Object();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);
	set_c(o, "c", 'A');

	s = FormattedString("oh hai der #%d %s!", 1, "penguin");
	call(s, "append", " FOO FIGHTERS");
	printf("%d\n", get_d(s, "length"));

	v = Vector(10);
	call(v, "append", o);
	call(v, "append", s);
	printf("%d\n", get_d(v, "count"));

	obj* ll = LinkedList();
	call(ll, "push back", s);
	call(ll, "push front", o);
	printf("%s\n", get_s(call_o(ll, "back"), "value"));
	printf("%d\n", get_d(call_o(ll, "front"), "d"));

	release(ll);
}

void end() {
	obj* o = call_o(v, "remove_at", 0);
	obj* s = call_o(v, "remove_at", 0);
	
	printf("%s %d %f %c\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"), get_c(o, "c"));

	printf("%s\n", get_s(s, "value"));

	printf("%c\n", call_c(s, "char at", 5));

	o = release(o);
	v = release(v);
}
