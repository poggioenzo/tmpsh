#include "newline_keypress.h"
#include "libft.h"
#include "newline_utils.h"

/*
** char_parsing:
**
** Loop over each char of the shell representation, and perform a specific action
** depending of the char. Manipulating a chained list of t_operand to store which
** operator is used.
** Is used to see if some operator aren't close or if we have to go to a new line
** if an operator expect it.
**
** return value (with pointer):
** - Will return the operand list at his current state.
** - MALLOC_SUCCESS/SUCCESS if everything append properly.
** - the enum invalid_syntax if there is a syntax error.
** - MALLOC_ERROR if a memory allocation failed.
*/

static void		char_parsing(t_line *shell_repr, t_operand  **operand_list, int *go_line,\
				int *status)
{
	t_char	*curr_char;
	int			to_skip;

	curr_char = NULL;
	to_skip = 0;
	while (get_next_char(&shell_repr, &curr_char) && *status != invalid_syntax)
	{
		*go_line = FALSE;
		if (curr_char->letter == '\'')
			skip_quote(&shell_repr, &curr_char, operand_list);
		else if (curr_char->letter == '\\')
			escape_char(curr_char, shell_repr, go_line, &to_skip);
		else if (curr_char->letter == '{')
			push_operand(operand_list, CURSH, '{');
		else if (curr_char->letter == '(')
			push_operand(operand_list, SUBSH, '(');
		else if (curr_char->letter == '"')
			check_db_quote(operand_list);
		else if (ft_incharset(curr_char->letter, "&|"))
			*status = check_separator(operand_list, &curr_char, go_line);
		else if (ft_incharset(curr_char->letter, "<>$"))
			check_cmdsubst(operand_list, curr_char, &to_skip);
		else if (ft_incharset(curr_char->letter, "})"))
			*status = check_closing(operand_list, curr_char);
		skip_char(&shell_repr, &curr_char, &to_skip);
	}
}

/*
** is_nested:
**
** Check according to the char_parsing function if the current shell
** representation is nested or not, and if we have to go to newline.
**
** Return value :
** - TRUE if we have to go to a newline
** - not_nested enum if it's the end of the current command.
** - MALLOC_ERROR if an memory allocation failed.
** - invalid_syntax if the current string isn't valid
*/

int			is_nested(t_line *shell_repr, t_operand **operand_list)
{
	int		status;
	int		go_line;

	status = SUCCESS;
	go_line = FALSE;
	char_parsing(shell_repr, operand_list, &go_line, &status);
	if (status == invalid_syntax)
		return (invalid_syntax);
	else if (*operand_list || go_line)
		return (TRUE);
	return (not_nested);
}

/*
** newline_check:
**
** Whenever a newline is found, check if the current shell is nested or not,
** a new line will be created according to the result.
*/

int			newline_check(t_line *shell_repr, t_cursor *cursor)
{
	t_operand	*operand_list;
	int			status;
	
	operand_list = NULL;
	status = is_nested(shell_repr, &operand_list);
	if (status == TRUE)
		status = add_new_line(shell_repr, operand_list, cursor);
	free_operand_lst(&operand_list, 0);
	return (status);
}
