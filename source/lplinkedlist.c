
#include "lplinkedlist.h"

static void dealloc(obj* self, va_list* args);
static void list_op_release(void*);
static void push_back(obj*, va_list*);
static void push_front(obj*, va_list*);
static obj* back(obj* self, va_list* args);
static obj* front(obj* self, va_list* args);

obj* LinkedList() {
	obj* self = Object();
	self->dealloc = dealloc;

	list* list = ll_create();
	set_p(self, "value", &list, sizeof(struct llist_*));

	bind(self, "push back", push_back);
	bind(self, "push front", push_front);

	bind_o(self, "back", back);
	bind_o(self, "front", front);

	return self;
}

void dealloc(obj* self, va_list* args) {
	list* value = *((list**)get_p(self, "value"));
	ll_destroy(value, list_op_release);
}

void list_op_release(void* element) {
	release(element);
}

void push_back(obj* self, va_list* args) {
	obj* o = va_arg(*args, obj*);

	list* value = *((list**)get_p(self, "value"));
	ll_push_back(value, o);

	retain(o);
}

void push_front(obj* self, va_list* args) {
	obj* o = va_arg(*args, obj*);

	list* value = *((list**)get_p(self, "value"));
	ll_push_front(value, o);

	retain(o);
}

obj* back(obj* self, va_list* args) {
	list* value = *((list**)get_p(self, "value"));
	return ll_back(value);
}

obj* front(obj* self, va_list* args) {
	list* value = *((list**)get_p(self, "value"));
	return ll_front(value);
}

