
#include "lplinkedlist.h"

static void push_back(obj*, va_list*);
static obj* back(obj* self, va_list* args);

obj* LinkedList() {
	obj* self = Object();

	list* list = ll_create();
	set_p(self, "value", &list, sizeof(struct llist_*));

	bind(self, "push back", push_back);
	bind_o(self, "back", back);

	return self;
}

void push_back(obj* self, va_list* args) {
	obj* o = va_arg(*args, obj*);

	list* value = *((list**)get_p(self, "value"));
	ll_push_back(value, o);

	retain(o);
}

obj* back(obj* self, va_list* args) {
	list* value = *((list**)get_p(self, "value"));
	return ll_back(value);
}
