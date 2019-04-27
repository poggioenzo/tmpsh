#include "test_runner.h"
#include "t_char_insert.h"
#include "t_char_allocation.h"
#include "char_utils.h"

/*
** insert_char_test-> insert_char
**
** Check 4 situation:
** 1) When a pointer is asked from NULL (first insertion)
** 2) Adding a new char when we have only single node (second insertion)
** 3) Adding a new char when we have mutlpile node (third insertion)
** 4) Check if the size update for mutliple element (4th insert)
** 5) Add element from the second one to see if increment is done properly (5th insert)
*/

void	insert_char_test(void)
{
	int		x_test = 0;

	//Insert a char from a NULL pointer
	t_char *char_lst = NULL;
	t_char *reference_chars = NULL;
	int lock = TRUE;

	//Insert a single t_char from a null node
	insert_char(&char_lst, 'a', lock); 
	reference_chars = create_ref_list("a");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a second char
	insert_char(&char_lst, 'b', lock);
	reference_chars = create_ref_list("ab");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a third and a fourth t_char from the beginning
	//of the t_char lst. Check after each insertion
	//Three t_char:
	insert_char(&char_lst, 'c', lock);
	reference_chars = create_ref_list("acb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
	
	//Four t_char:
	insert_char(&char_lst, 's', lock);
	reference_chars = create_ref_list("ascb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Move on in our list, add a new char from the secod position and
	//see if our list is correct
	insert_char(&char_lst->next, 'W', lock);
	reference_chars = create_ref_list("asWcb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
}

void	insert_string_test(void)
{
	int		x_test = 0;

	//Utils for the whole test
	int lock = TRUE;
	t_char	*reference_chars = NULL;

	//Insert an empty string from a NULL pointer, should stay NULL
	t_char *char_lst = NULL;
	insert_string(&char_lst, "", lock);
	ASSERT_PTRCMP(x_test, char_lst, NULL);

	//Insert a string from a NULL pointer
	insert_string(&char_lst, "abc", lock);
	reference_chars = create_ref_list("abc");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a new string from the last t_char ('c') of the string
	insert_string(&char_lst->next->next, "def", lock);
	reference_chars = create_ref_list("abcdef");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert string from the second t_char ('b')
	insert_string(&char_lst->next, "123", lock);
	reference_chars = create_ref_list("ab123cdef");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
	
}

void	cursor_insert_first_line(void)
{
	int x_test = 0;
	
	//Create the test shell to perform cursor insertion
	t_line *result_shell = create_ref_shell("line0\nline1\nline2");

	//Create are variable for the test
	t_cursor cursor;
	t_line *reference_shell = NULL;

	//Insert a char 'G' in the (0,0) coordo
	cursor = (t_cursor){.row = 0, .column = 0};
	cursor_insert(result_shell, 'G', &cursor);
	
	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("Gline0\nline1\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 0);
	ASSERT_INTCMP(x_test, cursor.column, 1);


	//Insert a second char 'D' at the current cursor position (0,1)
	cursor_insert(result_shell, 'D', &cursor);

	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("GDline0\nline1\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 0);
	ASSERT_INTCMP(x_test, cursor.column, 2);

	//Insert a char at the end of the line
	cursor.column = char_lst_len(reference_shell->chars);
	cursor_insert(result_shell, '9', &cursor);

	//Check if the '9' is after the '0' of "GDline0".
	reference_shell = create_ref_shell("GDline09\nline1\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 0);
	ASSERT_INTCMP(x_test, cursor.column, char_lst_len(reference_shell->chars));
}


void	cursor_insert_second_line(void)
{
	int x_test = 0;
	
	//Create the test shell to perform cursor insertion
	t_line *result_shell = create_ref_shell("line0\nline1\nline2");

	//Create are variable for the test
	t_cursor cursor;
	t_line *reference_shell = NULL;

	//Insert a char 'G' in the (0,0) coordo
	cursor = (t_cursor){.row = 1, .column = 0};
	cursor_insert(result_shell, 'G', &cursor);
	
	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("line0\nGline1\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 1);
	ASSERT_INTCMP(x_test, cursor.column, 1);


	//Insert a second char 'D' at the current cursor position (0,1)
	cursor_insert(result_shell, 'D', &cursor);

	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("line0\nGDline1\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 1);
	ASSERT_INTCMP(x_test, cursor.column, 2);

	//Insert a char at the end of the line
	cursor.column = char_lst_len(reference_shell->next->chars);
	cursor_insert(result_shell, '9', &cursor);

	//Check if the '9' is after the '0' of "GDline0".
	reference_shell = create_ref_shell("line0\nGDline19\nline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 1);
	int line_len = char_lst_len(reference_shell->next->chars);
	ASSERT_INTCMP(x_test, cursor.column, line_len);
}

static void print_char_repr(int row, t_char *char_lst)
{
	while (char_lst)
	{
		ft_printf("%d : ", row);
		ft_printf("(%d, '%c')->", char_lst->position, char_lst->letter);
		char_lst = char_lst->next;
	}
	ft_printf("NULL\n");
}

static void	show_shell(t_line *shell_repr, char *message)
{
	ft_printf("%s :\n", message);
	while (shell_repr)
	{
		print_char_repr(shell_repr->position, shell_repr->chars);
		shell_repr = shell_repr->next;
	}
}


void	cursor_insert_third_line(void)
{
	int x_test = 0;
	
	//Create the test shell to perform cursor insertion
	t_line *result_shell = create_ref_shell("line0\nline1\nline2");

	//Create are variable for the test
	t_cursor cursor;
	t_line *reference_shell = NULL;

	//Insert a char 'G' in the (0,0) coordo
	cursor = (t_cursor){.row = 2, .column = 0};
	cursor_insert(result_shell, 'G', &cursor);
	show_shell(result_shell, "RESULT : ");
	
	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("line0\nline1\nGline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 2);
	ASSERT_INTCMP(x_test, cursor.column, 1);


	//Insert a second char 'D' at the current cursor position (0,1)
	cursor_insert(result_shell, 'D', &cursor);

	//Create our comparaison shell and perform the test
	reference_shell = create_ref_shell("line0\nline1\nGDline2");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 2);
	ASSERT_INTCMP(x_test, cursor.column, 2);

	//Insert a char at the end of the line
	cursor.column = char_lst_len(reference_shell->next->next->chars);
	cursor_insert(result_shell, '9', &cursor);

	//Check if the '9' is after the '0' of "GDline0".
	reference_shell = create_ref_shell("line0\nline1\nGDline29");
	ASSERT_TLINECMP(x_test, result_shell, reference_shell);
	//Check also if the pointer have incremented properly
	ASSERT_INTCMP(x_test, cursor.row, 2);
	int line_len = char_lst_len(reference_shell->next->next->chars);
	ASSERT_INTCMP(x_test, cursor.column, line_len);
}








