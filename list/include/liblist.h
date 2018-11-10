#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <limits.h>

#define LIST_DEFAULT_SIZE 128

//TODO fix the variable types - current setting will produce BUGs if 
// list reaches maximum size - it will not only if _elem_size is 1 otherwise 
// int will overflow
struct list
{
	int _allocated_size;
	int _logical_size;
	int _elem_size;
	void *_elems;
};


int 
list_init(struct list *lst, size_t size, size_t nmemb);

void 
list_for_each(struct list *lst,  
			  void (*operation)(void *addr, void *suppl),
			  void *suppl);

void *
list_get(struct list *lst,
		 unsigned int index);


int
list_append(struct list *lst,
			void *addr);

int 
list_length(struct list *lst);

void
list_free(struct list *lst, void *free_func(void *elem));

#ifdef __cplusplus
}
#endif