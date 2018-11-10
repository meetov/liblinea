#include <assert.h>
#include <stdio.h>

#include <liblist.h>

static void test_correct_init() {
	fprintf(stdout, "Starting LIST_INIT Test.\n");

 	struct list lst;
 	int size = sizeof(int);
 	int nmemb = 1000;
 	int result = list_init(&lst, size, nmemb);

	assert( result != -1 );
	assert( lst._logical_size == 0 );
	assert( lst._allocated_size == size * nmemb );

	list_free(&lst, NULL);
	fprintf(stdout, "List Initialization => Succesful\n");
}

static void test_append()
{
	fprintf(stdout, "Starting LIST_APPEND Test.");
	fprintf(stdout, " Will trigger at least 3 reallocations\n");
	int size = 12;


	struct list lst;
	list_init(&lst, sizeof(int), size / 4);

	for (int i = 0; i < size; ++i)
	{
		int appended = list_append(&lst, &i);
		assert(appended != -1);
	}


	assert(lst._logical_size == size);
	assert(lst._allocated_size == size * sizeof(int));

	fprintf(stdout, "LIST_APPEND => Succesful\n");

}


static void print_char(void *elem, void *stream)
{
	fprintf((FILE *)stream, "%c\n", *(char *)elem);
}

static void test_for_each()
{
	fprintf(stdout, "Starting FOR_EACH Test.\n");
	fprintf(stdout, "The numbers from 0 to 9 should be printed to stdout.");
	fprintf(stdout, "They are treated as one byte chars.\n");
	fprintf(stdout, "Visually verify if all is well.\n");

	struct list lst;
	list_init(&lst, sizeof(char), 2);

	for (char c = '0'; c <= '9'; c++)
	{
		list_append(&lst, &c);
	}

	list_for_each(&lst, print_char, stdout);
	fprintf(stdout, "Test Ended => Check result. \n");
}



int main() {
	test_correct_init();
	test_append();
	test_for_each();
	return 0;
}
