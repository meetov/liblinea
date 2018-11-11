#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <liblist.h>
#include "liblist-private.h"


int 
list_init(list_ptr lst, size_t size, size_t nmemb)
{
	int init_result = 0;
	size_t alloc_size = 0;

	if ( nmemb > LIST_MAX_LOG_SIZE )
	{
		init_result = -1;
	}
	else if ( size > LIST_MAX_ELEM_SIZE )
	{
		init_result = -1;
	}
	else
	{
		alloc_size = size * nmemb;
	}

	if (alloc_size == 0)
	{
		init_result = -1;
	}
	else 
	{
		lst->_elems = malloc(alloc_size);
		lst->_allocated_size = alloc_size;
		lst->_elem_size = size;
		lst->_logical_size = 0;
	}
	
	return init_result;
}

list_ptr
list_init_default()
{
	list_ptr lst = malloc(sizeof(struct list));
	lst->_elems = malloc(LIST_DEFAULT_ALLOC_SIZE);
	lst->_allocated_size = LIST_DEFAULT_ALLOC_SIZE;
	lst->_elem_size = LIST_DEFAULT_ELEM_SIZE;
	lst->_logical_size = 0;
	
	return lst;
}

void
list_free(struct list *lst, void *free_func(void *elem))
{
	if (free_func == NULL)
		free(lst->_elems);
	else
	{
		for(unsigned long i = 0; i < lst->_logical_size; ++i)
		{
			void *elem = list_get(lst, i);
			free_func(elem);
		}
	}

}

void
list_for_each(struct list *lst,  
			  void (*operation)(void *addr, void *suppl),
			  void *suppl)
{
	for(int i = 0; i < list_length(lst); ++i)
	{
		void *elem = list_get(lst, i);
		operation(elem, suppl);
	}
}


int
list_length(struct list *lst)
{
	return lst->_logical_size;
}


int
list_append(struct list *lst, void *addr)
{
	if ( _list_requires_realloc(lst) )
	{
		int extended = _list_extend_alloc_size(lst);
		if (extended == -1)
			return -1;
	}

	// TODO fix last_idnex variable type once struct has been fixed
	void *logical_end = _list_logical_end(lst);
	if ( memcpy(logical_end, addr, lst->_elem_size) != logical_end )
		return -1;

	lst->_logical_size += 1;

	return 0;
}

// TODO: fix index variable type
void *
list_get(struct list *lst, 
		 unsigned long index)
{
	if( ! (index < lst->_logical_size) )
		return NULL;
	
	int offset = lst->_elem_size * index;
	void *el_addr = (char *)lst->_elems + offset;
	return el_addr;
}


// extends by doubling the last allocated size
// TODO: check how to remedy from fail of realloc

static int
_list_extend_alloc_size(struct list *lst)
{
	lst->_allocated_size = lst->_allocated_size * 2;
	lst->_elems = realloc(lst->_elems, lst->_allocated_size);

	if (lst->_elems == NULL)
		return -1;
	return 0;
}


static bool
_list_requires_realloc(struct list *lst)
{
	bool is_full = false;
	unsigned long elems_mem_size = lst->_logical_size * lst->_elem_size;

	if (elems_mem_size >= lst->_allocated_size)
		is_full = true;

	return is_full;
}

static void *
_list_logical_end(struct list *lst)
{
	int offset = lst->_logical_size * lst->_elem_size;
	void *logical_end = (char *) lst->_elems + offset;
	return logical_end;
}

