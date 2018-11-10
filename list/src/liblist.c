// #include <liblist.h>
// #include <list/liblist.h>
// #include "list/liblist.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <liblist.h>
#include "liblist-private.h"

int 
list_init(struct list *lst, size_t size, size_t nmemb)
{
	int init_result = 0;
	lst->_elem_size = size; lst->_logical_size = nmemb;
	init_result = _list_init(lst);
	return init_result;
}

// TODO: maybe make it a variable-length argument? 
void
list_free(struct list *lst, void *free_func(void *elem))
{
	if (free_func == NULL)
		free(lst->_elems);
	else
	{
		for(int i = 0; i < lst->_logical_size; ++i)
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
list_append(struct list *lst,
			void *addr)
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
			  unsigned int index)
{
	if( ! (index >= 0 && index <= lst->_logical_size) )
		return NULL;
	
	int offset = lst->_elem_size * index;
	void *el_addr = (char *)lst->_elems + offset;
	return el_addr;
}


static int 
_list_init(struct list *lst) 
{
	if (! (lst->_elem_size >= 0) )
		return -1;

	if (! (lst->_logical_size >= 0) )
		return -1;

	if ( lst->_logical_size == 0 )
		lst->_logical_size = LIST_DEFAULT_SIZE;

	int chunk_size = lst->_logical_size * lst->_elem_size;
	lst->_logical_size = 0;

	
	if ( (lst->_elems = malloc(chunk_size)) == NULL )
		return -1;

	lst->_allocated_size = chunk_size;

	return 0;
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
	int elems_mem_size = lst->_logical_size * lst->_elem_size;

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

