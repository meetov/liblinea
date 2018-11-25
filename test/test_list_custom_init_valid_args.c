#include <list.h>
#include <stdio.h>
#include "../src/list.c"

int 
test_custom_init (void)
{
	int result = 0;
	struct list *lst = malloc(sizeof(struct list));
	size_t size = sizeof(void *);
	size_t nmemb = 12;
	size_t alloc_size = size * nmemb;
	int init_res = list_init( lst, size, nmemb );

	if ( init_res != 0 )
	{
		printf("\nCouldn't init with valid args\n");
		return -1;
	}

	if ( lst->_elem_size != size )
	{
		printf("\n_elem_size is not %lu\n", size);
		result += 1;
	}

	if ( lst->_allocated_size != alloc_size )
	{
		printf("\n_allocated_size is not %lu\n", alloc_size);
		result += 1;
	}

	if ( lst->_logical_size != 0 )
	{
		printf("\n_logical_size must be 0\n");
		result += 1;
	}

	if (lst->_elems == NULL)
	{
		printf("\npointer to data must not be NULL");
		result += 1;
	}

	return result;
}

int main()
{
	return(test_custom_init());
}
