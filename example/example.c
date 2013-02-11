
#include "libprototype.h"

obj* s;
obj* v;

void start() {
	obj* o = object();
	set_s(o, "s", "foo");
	set_d(o, "d", 5);
	set_f(o, "f", 3.14);
	set_c(o, "c", 'A');

	s = formatted_string("oh hai der #%d %s!", 1, "penguin");
	call(s, "append", " FOO FIGHTERS");

	printf("%ld\n", get_d(s, "length"));

	v = vector(10);
	call(v, "append", o);
	call(v, "append", s);

	printf("%ld\n", get_d(v, "capacity"));
}

void end() {
	obj* o = call_o(v, "remove_at", 0);
	
	printf("%s %ld %f %c\n", get_s(o, "s"), get_d(o, "d"), get_f(o, "f"), get_c(o, "c"));

	printf("%s\n", get_s(s, "value"));

	printf("%c\n", call_c(s, "charat", 5));

	o = release(o);
	v = release(v);
}
