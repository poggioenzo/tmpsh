#include "t_line_utils.h"
#include "t_line_allocation.h"
#include "libft.h"
#include "char_utils.h"

/*
** line_lst_len:
**
** Return the total lenght of the t_line chained list.
** Can be used from any starting point of the chained list.
*/

int			line_lst_len(t_line *shell_repr)
{
	while (shell_repr)
		shell_repr = shell_repr->next;
	return (shell_repr->position + 1);
}

/*
** update_line_lst:
**
** Update the position of each line in the t_line chained list.
*/

void		update_line_lst(t_line *shell_repr)
{
	int index;

	index = 0;
	while (shell_repr)
	{
		shell_repr->position = index++;
		shell_repr = shell_repr->next;
	}
}

/*
** get_last_line:
**
** Return the last line of a t_line chained list.
*/

t_line		*get_last_line(t_line *shell_repr)
{
	while (shell_repr->next)
		shell_repr = shell_repr->next;
	return (shell_repr);
}

/*
** extract_line:
**
** Free the given line selected by his address.
** Avoid deleting the first line.
*/

void		extract_line(t_line *shell_repr, t_line *to_del)
{
	t_line	*prev_node;

	if (to_del->position == 0)
		return ;
	while (shell_repr != to_del)
	{
		prev_node = shell_repr;
		shell_repr = shell_repr->next;
	}
	prev_node->next = shell_repr->next;
	free_t_line(&shell_repr, 0);
}


/*
** line_proper:
**
** Use to clean up the line wherever the cursor is positionned.
** Delete the unlocked part of a t_char list.
*/

void    line_proper(t_line *cursor_line)
{
    t_char  *char_lst;

    char_lst = cursor_line->chars;
    while (char_lst->next && char_lst->next->lock == TRUE)
        char_lst = char_lst->next;
    free_t_char_lst(&char_lst->next, 0);
}
