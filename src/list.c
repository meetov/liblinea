#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <list.h>
#include "list-private.h"

int list_init(list_ptr lst, size_t size, size_t nmemb) 
{
	int init_result = 0;
	size_t alloc_size = 0;

	if (nmemb > LIST_MAX_LOG_SIZE) {
		init_result = -1;
	} else if (size > LIST_MAX_ELEM_SIZE) {
		init_result = -1;
	} else {
		alloc_size = size * nmemb;
	}

	if (alloc_size == 0) {
		init_result = -1;
	} else {
		// lst->_elems = malloc(alloc_size);
		lst->_elems = calloc(nmemb, size);
		lst->_allocated_size = alloc_size;
		lst->_elem_size = size;
		lst->_logical_size = 0;
	}

	return( init_result );
}

list_ptr list_init_default()
{
	list_ptr lst = malloc(sizeof(struct list));
	lst->_elems = malloc(LIST_DEFAULT_ALLOC_SIZE);
	lst->_allocated_size = LIST_DEFAULT_ALLOC_SIZE;
	lst->_elem_size = LIST_DEFAULT_ELEM_SIZE;
	lst->_logical_size = 0;

	return (lst);
}

void list_free(struct list *lst, void *free_func(void *elem)) 
{
	if (free_func != NULL)
	{
		for (unsigned long i = 0; i < lst->_logical_size; ++i) 
		{
			void *elem = list_get(lst, i);
			free_func(elem);
		}
	}

	free(lst->_elems);
}

void list_for_each(struct list *lst, 
		   void (*operation)(void *addr, void *suppl),
		   void *suppl) 
{
	for (unsigned long i = 0; i < list_length(lst); ++i) 
	{
		void *elem = list_get(lst, i);
		operation(elem, suppl);
	}
}

unsigned long list_length(struct list *lst) 
{
	return lst->_logical_size;
}

int list_append(struct list *lst, void *addr) 
{
	int result = 0;

	if (list_requires_realloc(lst)) 
		result = list_extend_alloc_size(lst);

	if (result != -1)
	{
		void *logical_end = list_logical_end(lst);
		memcpy(logical_end, addr, lst->_elem_size);
		lst->_logical_size += 1;
	}

	return( result );
}

void *
list_get(struct list *lst, unsigned long index) 
{
	void *el_addr;
	if ( (index >= lst->_logical_size) || (index > LIST_MAX_LOG_SIZE) )
	{
		el_addr = NULL;
	}
	else
	{
		unsigned long offset = lst->_elem_size * index;
		el_addr = (char *) lst->_elems + offset;
	}

	return( el_addr );
}

/*
 * TODO: check how to remedy from fail of realloc
 */

int list_extend_alloc_size(struct list *lst) 
{
	int allocate_code = 0;
	unsigned long new_alloc_size = lst->_allocated_size * 2UL;

	if (new_alloc_size > LIST_MAX_ALLOC_SIZE)
		allocate_code = -1;
	else
	{
		lst->_elems = realloc(lst->_elems, new_alloc_size);
		lst->_allocated_size = new_alloc_size;
	}

	return( allocate_code );
}

bool list_requires_realloc(struct list *lst) 
{
	bool is_full = false;
	unsigned long elems_mem_size = lst->_logical_size * lst->_elem_size;

	if (elems_mem_size >= lst->_allocated_size)
		is_full = true;

	return( is_full );
}

void *
list_logical_end(struct list *lst) 
{
	unsigned long offset = lst->_logical_size * lst->_elem_size;
	void *logical_end = (char *) lst->_elems + offset;
	return( logical_end );
}

