#include "char_skip.h"
#include "newline_utils.h"
#include "newline_keypress.h"

/*
** skip_quote:
**
** Will move position in the shell representation until a single quote will
** be found.
*/

void	skip_quote(t_line **shell_repr, t_char **curr_char, \
		t_operand **operand_list)
{
	t_operand	*last_open;

	last_open = get_last_bracket(*operand_list);
	if (last_open && last_open->open_char == '"')
		return ;
	push_operand(operand_list, QUOTE, '\'');
	while (get_next_char(shell_repr, curr_char))
	{
		if ((*curr_char)->letter == '\'')
		{
			delete_last_operand(operand_list);
			break ;
		}
	}
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
