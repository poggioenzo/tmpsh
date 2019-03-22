#include "newline_keypress.h"
#include "t_char_insert.h"
#include "t_char_utils.h"
#include "t_line_utils.h"


/*
** get_next_char:
**
** get_next_line like function. From a t_line a and t_char, will move on
** char by char until the entire t_line have been parsed.
**
** return value:
** - 1 if the char move on.
** - 0 if there isn't no more char to select.
*/

int		get_next_char(t_line **shell_repr, t_char **current_char)
{
	if (!*current_char && *shell_repr)
	{
		*current_char = get_unlocked_char((*shell_repr)->chars);
		if (!*current_char)
		{
			*shell_repr = (*shell_repr)->next;
			return (get_next_char(shell_repr, current_char));
		}
		return (1);
	}
	else if (!*current_char && !*shell_repr)
		return (0);
	else if ((*current_char)->next)
	{
		*current_char = (*current_char)->next;
		return (1);
	}
	else if (!(*current_char)->next && (*shell_repr)->next)
	{
		*shell_repr = (*shell_repr)->next;
		*current_char = NULL;
		return (get_next_char(shell_repr, current_char));
	}
	return (0);
}

/*
** is_next_char:
**
** Check if the given t_char element is having a specified char as
** next letter.
*/

int		is_next_char(t_char *curr_char, char c)
{
	if (c == '\n')
		return (curr_char->next == NULL);
	return (curr_char->next && curr_char->next->letter == c);
}

void	test_gnc(t_line *shell_repr)
{
	t_char *new_char;

	new_char = NULL;
	while (get_next_char(&shell_repr, &new_char))
	{
		ft_dprintf(fd_debug, "%c", new_char->letter);
	}
}


static int	is_nested(t_line *shell_repr)
{
	UNUSED(shell_repr);
	return (TRUE);
}

int			newline_check(t_line *shell_repr, t_cursor *cursor)
{
	test_gnc(shell_repr);
	if (is_nested(shell_repr) == TRUE)
	{
		if (push_end_line(&shell_repr) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		shell_repr = get_last_line(shell_repr);
		if (insert_string(&shell_repr->chars, "> ", TRUE) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		cursor->row = shell_repr->position;
		cursor->column = char_lst_len(shell_repr->chars);
		return (SUCCESS);
	}
	else
	{
		return (SUCCESS);
	}
}
