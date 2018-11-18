#include <list.h>
#include "minunit.h"
#include "../src/list.c"

MU_TEST( test_default_init )
{
	list_ptr lst = list_init_default();
	mu_check( lst->_elem_size == LIST_DEFAULT_ELEM_SIZE );
	mu_check( lst->_allocated_size == LIST_DEFAULT_ALLOC_SIZE );
	mu_check( lst->_logical_size == 0 );
}

MU_TEST_SUITE( test_list_init )
{
	MU_RUN_TEST( test_default_init );
}

int main()
{
	MU_RUN_SUITE( test_list_init );
	MU_REPORT();
	return(0);
}
