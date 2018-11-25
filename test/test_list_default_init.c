#include <list.h>
#include <stdio.h>
#include "../src/list.c"

int 
test_default_init (void)
{
	int result = 0;
	struct list *lst = list_init_default();

	if ( lst->_elem_size != LIST_DEFAULT_ELEM_SIZE )
	{
		printf("\n_elem_size is not default\n");
		result += 1;
	}

	if ( lst->_allocated_size != LIST_DEFAULT_ALLOC_SIZE )
	{
		printf("\n_allocated_size is not default\n");
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
	return(test_default_init());
}
