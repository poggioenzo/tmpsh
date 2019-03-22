#include "libft.h"
#include "newline_keypress.h"
#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_line_utils.h"
#include "t_bracket_utils.h"
#include "get_next_char.h"

void		show_operand_lst(t_operand *operand_list);

/*
** syntax_error:
**
** Small utils to write the char who is raising a syntax error.
*/

int		syntax_error(char operator)
{
	ft_dprintf(2, "tmpsh: Invalid syntax near %c\n", operator);
	return (invalid_syntax);
}


/*
** skip_quote:
**
** Will move position in the shell representation until a single quote will
** be found.
**
** return value:
** - SUCCESS if we reach the end of the shell representation, or if a single
** quote have been found.
** - MALLOC_ERROR if an allocation error occur.
*/

int		skip_quote(t_line **shell_repr, t_char **curr_char, \
				t_operand **operand_list)
{
	t_operand	*last_open;

	last_open = get_last_bracket(*operand_list);
	if (last_open && last_open->open_char == '"')
		return (SUCCESS);
	if (push_operand(operand_list, QUOTE, '\'') == MALLOC_ERROR)
		   return (MALLOC_ERROR);
	while (get_next_char(shell_repr, curr_char))
	{
		if ((*curr_char)->letter == '\'')
		{
				delete_last_operand(operand_list);
				return (SUCCESS);
		}
	}
	return (SUCCESS);
}

/*
** escape_char:
**
** If a newline is found after an escape character, expect to go to a newline.
** If it's an other character, skip it to escape it.
*/

void	escape_char(t_char *curr_char, t_line *shell_repr, int *go_line, \
		int *char_to_skip)
{
	if (is_next_char(curr_char, '\n'))
	{
		if (!shell_repr->next)
			*go_line = TRUE;
	}
	else
		*char_to_skip += 1;
}


/*
** get_separator_type:
**
** Check which kind of separator the current char is between |, || and &&.
** Add the right type to the operand chained list.
** Ask to skip a char if the separator is using to char.
**
** return value:
** - MALLOC_SUCCESS if the separator have been added, or if it's the
** background & operator, and we skeep it.
** - MALLOC_ERROR if an memory allocation failed.
*/

int		get_separator_type(t_operand **operand_list, t_char *curr_char,\
				int *skip_char)
{
	int		status;

	status = MALLOC_SUCCESS;
	if (curr_char->letter == '&')
	{
		if (!is_next_char(curr_char, '&'))
			return (status);
		status = push_operand(operand_list, CMDAND, '\0');
		*skip_char = TRUE;
	}
	else if (curr_char->letter == '|')
	{
		if (is_next_char(curr_char, '|'))
		{
			status = push_operand(operand_list, CMDOR, '\0');
			*skip_char = TRUE;
		}
		else
			status = push_operand(operand_list, PIPE, '\0');
	}
	return (status);
}

/*
** check_separator:
**
** Check which kind of separator we have to append it to our operand list,
** and will verify if the end of the line is containing an other command
** with who the seperator is connecting to, otherwise, it will expect an other
** line.
**
** return value:
** - SUCCESS if we can continue the process properly.
** - MALLOC_ERROR if a memory allocation failed.
*/

int		check_separator(t_operand **operand_list, t_char **curr_char,\
				int *go_line)
{
		int		status;
		int		skip_char;

		skip_char = FALSE;
		status = get_separator_type(operand_list, *curr_char, &skip_char);
		if (status == MALLOC_ERROR)
			return (status);
		else if (status == leave_check)
			return (SUCCESS);
		if (skip_char)
			*curr_char = (*curr_char)->next;
		while ((*curr_char)->next && ft_isspace((*curr_char)->next->letter))
			*curr_char = (*curr_char)->next;
		if (charset_in_next_char(*curr_char, "&|;"))
			return (syntax_error((*curr_char)->next->letter));
		if ((*curr_char)->next)
			delete_last_operand(operand_list);
		else
			*go_line = TRUE;
		show_operand_lst(*operand_list);
		return (SUCCESS);
}

/*
** check_cmdsubst:
**
** Check if the given char is corresponding to a specific kind of substitution,
** it should match with <(), >(), $() or ${} substitution.
** If it's the case, append it to the operand chained list.
**
** return value:
** - MALLOC_SUCCESS if the command have been added to the chained list,
** of if the character isn't a substitution.
** - MALLOC_ERROR if an allocation failed.
*/

int		check_cmdsubst(t_operand **operand_list, t_char *curr_char, \
				int *to_skip)
{
	int		status;

	status = MALLOC_SUCCESS;
	if (ft_incharset(curr_char->letter, "<>"))
	{
		if (is_next_char(curr_char, '('))
			status = push_operand(operand_list, CMDSUBST, '(');
		else
			return (status);
	}
	else if (is_next_char(curr_char, '('))
		status = push_operand(operand_list, CMDSUBST, '(');
	else if (is_next_char(curr_char, '{'))
		status = push_operand(operand_list, BRACEPARAM, '{');
	else
		return (0);
	*to_skip += 1;
	return (status);
}

/*
** check_db_quote:
**
** Whenever a double quote is getting, check if it's closing an other double quote,
** otherwise add it to our current operand list.
**
** return value:
** - SUCCESS|MALLOC_SUCCESS if the allocation or deletion succeed.
** - MALLOC_ERROR if a memory allocation failed.
*/

int			check_db_quote(t_operand **operand_list)
{
	t_operand	*last_open;

	last_open = get_last_bracket(*operand_list);
	if (last_open && last_open->open_char == '"')
		delete_operand(operand_list, &last_open);
	else
		return (push_operand(operand_list, DQUOTE, '"'));
	return (SUCCESS);
}

/*
** check_closing:
**
** When a character corresponding to a closing element is found, ( or },
** check if it's closing the right operand.
** If it's closing the right element, remove it from our operand list,
** remove also all the separator inside the opening.
**
** return value:
** - SUCCESS if it's matching the correct element or if it's skipped because of quote.
** - the enum invalid_syntax if the closing element is closing the wrong one.
*/

int		check_closing(t_operand **operand_list, t_char *curr_char)
{
	t_operand *last_open;

	last_open = get_last_bracket(*operand_list);
	if (last_open)
	{
		if (last_open->open_char == '"')
			return (SUCCESS);
		if (last_open->open_char == '(' && curr_char->letter == ')')
			delete_operand_from(operand_list, &last_open);
		else if (last_open->open_char == '{' && curr_char->letter == '}')
			delete_operand_from(operand_list, &last_open);
		else
			return (syntax_error(last_open->open_char));
	}
	else
		return (syntax_error(curr_char->letter));
	return (SUCCESS);
}

/*
** skip_char:
**
** Use get_next_char to skip a specific number of char, used when a operator
** is using multiple character.
*/

void		skip_char(t_line **shell_repr, t_char **curr_char, int *to_skip)
{
	while (*to_skip && get_next_char(shell_repr, curr_char))
		*to_skip -= 1;
}

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
	while (get_next_char(&shell_repr, &curr_char) && *status == MALLOC_SUCCESS)
	{
		*go_line = FALSE;
		if (curr_char->letter == '\'')
			*status = skip_quote(&shell_repr, &curr_char, operand_list);
		else if (curr_char->letter == '\\')
			escape_char(curr_char, shell_repr, go_line, &to_skip);
		else if (curr_char->letter == '{')
			*status = push_operand(operand_list, CURSH, '{');
		else if (curr_char->letter == '(')
			*status = push_operand(operand_list, SUBSH, '(');
		else if (curr_char->letter == '"')
			*status = check_db_quote(operand_list);
		else if (ft_incharset(curr_char->letter, "&|"))
			*status = check_separator(operand_list, &curr_char, go_line);
		else if (ft_incharset(curr_char->letter, "<>$"))
			*status = check_cmdsubst(operand_list, curr_char, &to_skip);
		else if (ft_incharset(curr_char->letter, "})"))
			*status = check_closing(operand_list, curr_char);
		skip_char(&shell_repr, &curr_char, &to_skip);
	}
}

/*
** is_nested:
**
**
*/

int			is_nested(t_line *shell_repr, t_operand **operand_list)
{
	int		status;
	int		go_line;

	status = MALLOC_SUCCESS;
	go_line = FALSE;
	char_parsing(shell_repr, operand_list, &go_line, &status);
	if (status == invalid_syntax)
		return (invalid_syntax);
	else if (status == MALLOC_ERROR)
		return (MALLOC_ERROR);
	else if (*operand_list || go_line)
		return (TRUE);
	return (not_nested);
}

char	**fill_operand_table(void)
{
	char	**operand_strings;

	if (!(operand_strings = (char **)malloc(sizeof(char *) * NBRE_OPERAND + 100)))
		return (NULL);
	operand_strings[CMDSUBST] = CMDSUBST_STR;
	operand_strings[BRACEPARAM] = BRACEPARAM_STR;
	operand_strings[CURSH] = CURSH_STR;
	operand_strings[SUBSH] = SUBSH_STR;
	operand_strings[DQUOTE] = DQUOTE_STR;
	operand_strings[QUOTE] = QUOTE_STR;
	operand_strings[CMDAND ^ SEPARATOR] = CMDAND_STR;
	operand_strings[CMDOR ^ SEPARATOR] = CMDOR_STR;
	operand_strings[PIPE ^ SEPARATOR] = PIPE_STR;
	return (operand_strings);
}

int		free_operand_table(char ***operand_strings, int status)
{
	free(*operand_strings);
	*operand_strings = NULL;
	return (status);
}

int		fill_all_strings(char ***operand_strings, t_operand *operand_list, \
				char **joined_separator)
{
	int		allocated;
	char	*tmp_str;
	char	*new_operand;

	if (!(*joined_separator = ft_strnew(0)))
		return (MALLOC_ERROR);
	tmp_str = " ";
	while (operand_list)
	{
		allocated = FALSE;
		new_operand = (*operand_strings)[operand_list->type % SEPARATOR];
		if (operand_list->next)
		{
			allocated = TRUE;
			if (!(new_operand = ft_strjoin(new_operand, tmp_str)))
				return (MALLOC_ERROR);
		}
		*joined_separator = ft_fstrjoin(joined_separator, &new_operand, 1, allocated);
		if (*joined_separator == NULL)
			return (MALLOC_ERROR);
		operand_list = operand_list->next;
	}
	return (MALLOC_SUCCESS);
}

int		format_operand_string(t_operand *operand_list, char **operand_str)
{
	int		status;
	char	**operand_strings;
	char	*joined_separator;

	if (!(operand_strings = fill_operand_table()))
		return (MALLOC_ERROR);
	if (!(*operand_str = (char *)malloc(sizeof(char) * 3)))
		return (free_operand_table(&operand_strings, MALLOC_ERROR));
	ft_strcpy(*operand_str, "> ");
	status = fill_all_strings(&operand_strings, operand_list, &joined_separator);
	free_operand_table(&operand_strings, 0);
	if (status == MALLOC_ERROR)
		return (ft_strdel_out(operand_str, MALLOC_ERROR));
	*operand_str = ft_fstrjoin(&joined_separator, operand_str, TRUE, TRUE);
	return (*operand_str ? MALLOC_SUCCESS : MALLOC_ERROR);
}

int			add_new_line(t_line *shell_repr, t_operand *operand_list, \
				t_cursor *cursor)
{
	char	*operand_str;
	int		status;

	if (push_end_line(&shell_repr) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (format_operand_string(operand_list, &operand_str) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	shell_repr = get_last_line(shell_repr);
	status = insert_string(&shell_repr->chars, operand_str, TRUE);
	ft_strdel(&operand_str);
	if (status == MALLOC_ERROR)
		return (status);
	cursor->row = shell_repr->position;
	cursor->column = char_lst_len(shell_repr->chars);
	return (status);
}


void		show_operand_lst(t_operand *operand_list)
{
	if (!operand_list)
		ft_dprintf(fd_debug, "NO OPERAND IN LIST\n");
	else
	{
		while (operand_list)
		{
			ft_dprintf(fd_debug, "{operand :%d}-->", operand_list->type);
			operand_list = operand_list->next;
		}
		ft_dprintf(fd_debug, "NULL\n");
	}
}

int			newline_check(t_line *shell_repr, t_cursor *cursor)
{
	t_operand	*operand_list;
	int			status;
	
	operand_list = NULL;
	status = is_nested(shell_repr, &operand_list);
	ft_dprintf(fd_debug, "NESTED : %d\n", status);
	if (status == TRUE)
		add_new_line(shell_repr, operand_list, cursor);
	free_operand_lst(&operand_list, 0);
	return (status);
}
