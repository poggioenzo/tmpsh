#include "get_next_char.h"
#include "t_char_utils.h"

/*
** is_next_char:
**
** Check if the next char is which expected in the parameter.
**
** return value:
** - 1 if the next char is corresponding, 0 otherwise.
*/

int	is_next_char(t_char *curr_char, char letter)
{
	if (letter == '\n' && !curr_char->next)
			return (1);
	return (curr_char->next && curr_char->next->letter == letter);
}

/*
** charset_in_next_char:
**
** Check if one char of the given charset is in the next char.
** 
** return value:
** - 1 if one char is corresponding to the next char, 0 otherwise.
*/

int	charset_in_next_char(t_char *curr_char, char *charset)
{
	while (*charset)
	{
		if (is_next_char(curr_char, *charset++))
				return (1);
	}
	return (0);
}


/*
** get_next_char:
**
** Kind of get_next_line to go through the entire shell representation
** and move char by char unsing one t_line and one t_char.
**
** return value:
** - 1 if the next char is found.
** - 0 if there is no more char to get.
*/

int		get_next_char(t_line **shell_repr, t_char **curr_char)
{
	if (!*curr_char && *shell_repr)
		{
		*curr_char = get_unlocked_char((*shell_repr)->chars);
		if (!*curr_char)
		{
			*shell_repr = (*shell_repr)->next;
			return (get_next_char(shell_repr, curr_char));
		}
		return (1);
	}
	else if (!*curr_char && !*shell_repr)
			return (0);
	else if ((*curr_char)->next)
			*curr_char = (*curr_char)->next;
	else if (!(*curr_char)->next)
	{
		*shell_repr = (*shell_repr)->next;
		*curr_char = NULL;
		return (get_next_char(shell_repr, curr_char));
	}
	return (1);
}
