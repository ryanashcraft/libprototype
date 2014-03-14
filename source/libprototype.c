
#include "libprototype.h"

void start();
void end();

static void error_called_method_on_null(char* key);
static void error_attempted_to_set_member_of_null(char* key);
static void error_attempted_to_set_member_to_null(char* key);
static void error_object_does_not_respond_to_method(char* key);
static void error_attempted_to_get_undefined_member(char* key);

obj* Object() {
	obj* o = malloc(sizeof(struct _obj));
	assert(o);

	o->table = ht_create(4, 2);
	o->retain_count = 1;
	o->dealloc = NULL;

	return o;
}

obj* clone(obj* subject) {
	obj* clone = malloc(sizeof(struct _obj));
	assert(clone);

	memcpy(clone, subject, sizeof(struct _obj));

	return clone;
}

void retain(obj* o) {
	o->retain_count++;
}

obj* release(obj* o) {
	--o->retain_count;

	if (o->retain_count <= 0) {
		return delete(o);
	}

	return o;
}

obj* delete(obj* o) {
	if (o->dealloc != NULL)
		o->dealloc(o, NULL);
	
	ht_destroy(o->table);
	free(o);

	return NULL;
}

void bind(obj* o, char* key, fpointer function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer));
}

void bind_o(obj* o, char* key, fpointer_o function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_o));
}

void bind_p(obj* o, char* key, fpointer_p function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_p));
}

void bind_d(obj* o, char* key, fpointer_d function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_d));
}

void bind_ld(obj* o, char* key, fpointer_ld function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_ld));
}

void bind_f(obj* o, char* key, fpointer_f function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_f));
}

void bind_c(obj* o, char* key, fpointer_c function) {
	ht_insert(&o->table, key, strlen(key), &function, sizeof(fpointer_c));
}

void call(obj* o, char* key, ...) {
	va_list argp;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer *m = (fpointer*)ht_get(o->table, key, strlen(key));

	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	(*m)(o, &argp);
	va_end(argp);
}

obj* call_o(obj* o, char* key, ...) {
	va_list argp;
	obj* result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_o *m = (fpointer_o*)ht_get(o->table, key, strlen(key));

	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

void* call_p(obj* o, char* key, ...) {
	va_list argp;
	void* result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_p *m = (fpointer_p*)ht_get(o->table, key, strlen(key));

	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

int call_d(obj* o, char* key, ...) {
	va_list argp;
	int result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_d *m = (fpointer_d*)ht_get(o->table, key, strlen(key));

	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

long call_ld(obj* o, char* key, ...) {
	va_list argp;
	long result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_ld *m = (fpointer_ld*)ht_get(o->table, key, strlen(key));

	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

double call_f(obj* o, char* key, ...) {
	va_list argp;
	double result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_f *m = (fpointer_f*)ht_get(o->table, key, strlen(key));
	
	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

char call_c(obj* o, char* key, ...) {
	va_list argp;
	char result;
	va_start(argp, key);

	if (o == NULL) {
		error_called_method_on_null(key);
	}

	fpointer_c *m = (fpointer_c*)ht_get(o->table, key, strlen(key));
	
	if (m == NULL) {
		error_object_does_not_respond_to_method(key);
	}

	result = (*m)(o, &argp);
	va_end(argp);
	return result;
}

void set_o(obj* o, char* key, obj* value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	if (value == NULL) {
		error_attempted_to_set_member_to_null(key);
	}

	ht_insert(&o->table, key, strlen(key) + 1, value, sizeof(struct _obj));
}

obj* get_o(obj* o, char* key) {
	obj* valuep = ht_get(o->table, key, strlen(key) + 1);

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return valuep;
}

void set_p(obj* o, char* key, void* value, size_t value_size) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	if (value == NULL) {
		error_attempted_to_set_member_to_null(key);
	}

	ht_insert(&o->table, key, strlen(key) + 1, value, value_size);
}

void* get_p(obj* o, char* key) {
	void* valuep = ht_get(o->table, key, strlen(key) + 1);

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return valuep;
}

void set_s(obj* o, char* key, char* value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	if (value == NULL) {
		error_attempted_to_set_member_to_null(key);
	}

	ht_insert(&o->table, key, strlen(key) + 1, value, strlen(value) + 1);
}

char* get_s(obj* o, char* key) {
	char* valuep = ht_get(o->table, key, strlen(key) + 1);
	
	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return valuep;
}

void set_d(obj* o, char* key, int value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	int* valuep = malloc(sizeof(int));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(int));
	free(valuep);
}

int get_d(obj* o, char* key) {
	int* valuep = ht_get(o->table, key, strlen(key));

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return *valuep;
}

void set_ld(obj* o, char* key, long value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	long* valuep = malloc(sizeof(long));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(long));
	free(valuep);
}

long get_ld(obj* o, char* key) {
	long* valuep = ht_get(o->table, key, strlen(key));

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return *valuep;
}

void set_f(obj* o, char* key, double value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	double* valuep = malloc(sizeof(double));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(double));
	free(valuep);
}

double get_f(obj* o, char* key) {
	double* valuep = ht_get(o->table, key, strlen(key));

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}

	return *valuep;
}

void set_c(obj* o, char* key, char value) {
	if (o == NULL) {
		error_attempted_to_set_member_of_null(key);
	}

	char* valuep = malloc(sizeof(char));
	*valuep = value;
	ht_insert(&o->table, key, strlen(key), valuep, sizeof(char));
	free(valuep);
}

char get_c(obj* o, char* key) {
	char* valuep = ht_get(o->table, key, strlen(key));

	if (valuep == NULL) {
		error_attempted_to_get_undefined_member(key);
	}
	
	return *valuep;
}

void unset(obj* o, char* key) {
	ht_remove(o->table, key, strlen(key));
}


void error_called_method_on_null(char* key) {
	LOG_CRITICAL("Attempted to call \"%s\" on NULL", key);
	abort();
}

void error_attempted_to_set_member_of_null(char* key) {
	LOG_CRITICAL("Attempted to set member \"%s\" of NULL", key);
	abort();
}

void error_attempted_to_set_member_to_null(char* key) {
	LOG_CRITICAL("Attempted to set member \"%s\" to NULL", key);
	abort();
}

void error_object_does_not_respond_to_method(char* key) {
	LOG_CRITICAL("Object does not respond to call \"%s\"", key);
	abort();
}

void error_attempted_to_get_undefined_member(char* key) {
	LOG_CRITICAL("Attempted to get undefined member \"%s\"", key);
	abort();
}

int main() {
	start();
	atexit(end);
}
