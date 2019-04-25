#include "test_runner.h"
#include "t_cursor_utils.h"

/*
** t_cursor_alloc_test:
**
** Tests for alloc_cursor and dealloc_cursor.
*/

void	t_cursor_alloc_test(void)
{
	int		x_test = 0;

	//Create a cursor from a NULL pointer.
	t_cursor	*cursor = NULL;
	alloc_cursor(&cursor);

	//Check if the cursor have the good propreties
	ASSERT_TEST(x_test, cursor != NULL);
	ASSERT_INTCMP(x_test, cursor->column, 0);
	ASSERT_INTCMP(x_test, cursor->row, 0);

	//Free the pointer and check if it become a NULL pointer
	dealloc_cursor(&cursor, 0);
	ASSERT_PTRCMP(x_test, cursor, NULL);
}
