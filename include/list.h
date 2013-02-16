
#ifndef LIST_H_
#define LIST_H_

#include <stdarg.h>

typedef void (*list_op)(void*);
typedef void (*list_op_args)(void*, va_list *);
typedef int (*list_pred)(const void*);
typedef int (*list_pred_args)(const void*, va_list *);
typedef int (*equal_op)(const void*, const void*);
typedef int (*comp_op)(const void*, const void*);

struct lnode;

typedef struct llist {
  struct lnode* head;
  unsigned int size;
  comp_op sort_op;
} list;

/* Creating */
list* ll_create(void);

/* Sort */
void ll_set_sort_op(list *llist, comp_op comp_func);

/* Adding */
void ll_push_front(list* llist, void* data);
void ll_push_back(list* llist, void* data);
void ll_push_in_order(list* llist, void* data);

/* Removing */
int ll_remove_front(list* llist, list_op free_func);
int ll_remove_index(list* llist, int index, list_op free_func);
int ll_remove_back(list* llist, list_op free_func);
int ll_remove_data(list* llist, const void* data, equal_op compare_func, list_op free_func);
int ll_remove_if(list* llist, list_pred pred_func, list_op free_func);

/* Querying List */
void* ll_front(list* llist);
void* ll_back(list* llist);
void* ll_get_index(list* llist, int index);
void* ll_get_first_occurrence(list* llist, list_pred_args test_func, ...);
int ll_is_empty(list* llist);
int ll_size(list* llist);

/* Searching */
int ll_find_occurrence(list* llist, const void* search, equal_op compare_func);

/* Freeing */
void ll_empty_list(list* llist, list_op free_func);
void ll_destroy(list *llist, list_op free_func);

/* Traversal */
void ll_traverse(list* llist, list_op do_func);
void ll_traverse_with_args(list* llist, list_op_args do_func, ...);

#endif
