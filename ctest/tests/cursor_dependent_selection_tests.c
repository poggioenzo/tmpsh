#include "test_runner.h"
#include "cursor_dependent_selection.h"
#include "char_selection.h"

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
	t_char *prev_char = NULL; t_char *cursor_char = NULL;

	//Get the first element of the shell
	cursor = (t_cursor){.row = 0, .column = 0};
	cursor_char = get_cursor_char(&cursor, test_shell->chars, &prev_char);

	//Test if the returned t_char for the cursor if the right one
	ASSERT_PTRCMP(x_test, cursor_char, test_shell->chars);
	ASSERT_PTRCMP(x_test, prev_char, NULL);

	//Test to have the 'n' of "line0" string at the third position
	cursor.column = 2;
	cursor_char = get_cursor_char(&cursor, test_shell->chars, &prev_char);

	//Test if the cursor char is 'n' and the prev char is 'i'
	ASSERT_PTRCMP(x_test, cursor_char, test_shell->chars->next->next);
	ASSERT_PTRCMP(x_test, prev_char, test_shell->chars->next);

	//Test finally if we can have the cursor at the ent of the t_char list,
	//at the 5 index ('\0') of "line0".
	cursor.column = 5;
	cursor_char = get_cursor_char(&cursor, test_shell->chars, &prev_char);

	//Test if the cursor_char is NULL
	ASSERT_PTRCMP(x_test, cursor_char, NULL);

	//Test if the previous char is effectively '0' in "line0"
	t_char *last_char_reference = NULL;
	get_last_char(test_shell->chars, &last_char_reference);
	ASSERT_PTRCMP(x_test, prev_char, last_char_reference); 
}
