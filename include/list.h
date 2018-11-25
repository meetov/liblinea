#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <limits.h>

#define LIST_MAX_LOG_SIZE UINT_MAX
#define LIST_MAX_ELEM_SIZE INT_MAX
#define LIST_MAX_ALLOC_SIZE                                                    \
	(unsigned long)LIST_MAX_LOG_SIZE *(unsigned long)LIST_MAX_ELEM_SIZE

#define LIST_DEFAULT_INITIAL_SIZE 1024U
#define LIST_DEFAULT_ALLOC_SIZE LIST_DEFAULT_INITIAL_SIZE * sizeof(void *)
#define LIST_DEFAULT_ELEM_SIZE sizeof(void *)

struct list {
	unsigned long _allocated_size;
	unsigned long _logical_size;
	unsigned long _elem_size;
	void *_elems;
};

int list_init(struct list *lst, size_t size, size_t nmemb);

struct list *list_init_default();

void list_for_each(struct list *lst, void (*operation)(void *addr, void *suppl),
		   void *suppl);

void *list_get(struct list *lst, unsigned long index);

int list_append(struct list *lst, void *addr);

unsigned long list_length(struct list *lst);

void list_free(struct list *lst, void *free_func(void *elem));

#ifdef __cplusplus
}
#endif
