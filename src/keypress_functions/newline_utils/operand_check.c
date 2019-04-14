#include "operand_check.h"
#include "t_operand_allocation.h"
#include "newline_keypress.h"
#include "get_next_char.h"
#include "operand_deletion.h"
#include "t_operand_utils.h"
#include "libft.h"

/*
** get_separator_type:
**
** Check which kind of separator the current char is between |, || and &&.
** Add the right type to the operand chained list.
** Ask to skip a char if the separator is using to char.
*/

static void		get_separator_type(t_operand **operand_list, t_char *curr_char,\
				int *skip_char)
{
	if (curr_char->letter == '&')
	{
		if (is_next_char(curr_char, '&'))
		{
			push_operand(operand_list, CMDAND, '\0');
			*skip_char = TRUE;
		}
	}
	else if (curr_char->letter == '|')
	{
		if (is_next_char(curr_char, '|'))
		{
			push_operand(operand_list, CMDOR, '\0');
			*skip_char = TRUE;
		}
		else
			push_operand(operand_list, PIPE, '\0');
	}
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
** - syntax_error.
*/

int		check_separator(t_operand **operand_list, t_char **curr_char,\
				int *go_line)
{
		int		skip_char;

		skip_char = FALSE;
		get_separator_type(operand_list, *curr_char, &skip_char);
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
		return (SUCCESS);
}

/*
** check_cmdsubst:
**
** Check if the given char is corresponding to a specific kind of substitution,
** it should match with <(), >(), $() or ${} substitution.
** If it's the case, append it to the operand chained list.
*/

void	check_cmdsubst(t_operand **operand_list, t_char *curr_char, \
				int *to_skip)
{
	if (ft_incharset(curr_char->letter, "<>"))
	{
		if (is_next_char(curr_char, '('))
			push_operand(operand_list, CMDSUBST, '(');
		else
			return ;
	}
	else if (is_next_char(curr_char, '('))
		push_operand(operand_list, CMDSUBST, '(');
	else if (is_next_char(curr_char, '{'))
		push_operand(operand_list, BRACEPARAM, '{');
	else
		return ;
	*to_skip += 1;
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

void		check_db_quote(t_operand **operand_list)
{
	t_operand	*last_open;

	last_open = get_last_bracket(*operand_list);
	if (last_open && last_open->open_char == '"')
		delete_operand(operand_list, &last_open);
	else
		push_operand(operand_list, DQUOTE, '"');
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
		return (SUCCESS);
	}
	return (syntax_error(curr_char->letter));
}
