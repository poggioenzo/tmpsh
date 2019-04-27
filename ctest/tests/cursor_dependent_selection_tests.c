#include "test_runner.h"
#include "cursor_dependent_selection.h"

void	get_cursor_line_test(void)
{
	int x_test = 0;

	//Create a shell with four lines.
	t_line	*test_shell = create_ref_shell("line0\nline1\nline2\nline3");

	//Create our variables to make selection
	t_cursor	cursor;
	t_line		*line_result;

	//Try to get the first line (index 0)
	cursor = (t_cursor){.row = 0, .column = 0};
	line_result = get_cursor_line(test_shell, &cursor);
	ASSERT_INTCMP(x_test, line_result->position, cursor.row);

	// Try to get the second line
	cursor.row = 1;
	line_result = get_cursor_line(test_shell, &cursor);
	ASSERT_INTCMP(x_test, line_result->position, cursor.row);

	//Try to get the third t_line
	cursor.row = 2;
	line_result = get_cursor_line(test_shell, &cursor);
	ASSERT_INTCMP(x_test, line_result->position, cursor.row);

	//Get the fourth line
	cursor.row = 3;
	line_result = get_cursor_line(test_shell, &cursor);
	ASSERT_INTCMP(x_test, line_result->position, cursor.row);
}
/*
** get_cursor_char_test -> get_cursor_char
**
** Select the t_char who corresponding to the cursor position, and his
** previous_node.
*/

void	get_cursor_char_test(void)
{
	int x_test = 0;

	//Create our reference shell
	t_line	*test_shell = create_ref_shell("line0\nline1\nline2\nline3");

	//Create our selection variables
	t_cursor cursor;
	t_char *prev_char; t_char *cursor_char;



}
