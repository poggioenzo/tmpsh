#include "t_line_utils.h"
#include "libft.h"
#include "t_char_utils.h"
/*
** free_t_line:
**
** Free a single t_line element.
*/

static int		free_t_line(t_line **line_lst, int status)
{
	t_char		*char_lst;

	char_lst = (*line_lst)->chars;
	free_t_char_lst(&char_lst, status);
	free(*line_lst);
	*line_lst = NULL;
	return (status);
}

/*
** free_t_line_lst:
**
** Free the entire chained list of t_line.
*/

int				free_t_line_lst(t_line **line_lst, int status)
{
	t_line		*curr_line;
	t_line		*next_line;

	curr_line = *line_lst;
	while (curr_line)
	{
		next_line = curr_line->next;
		free_t_line(&curr_line, status);
		curr_line = next_line;
	}
	*line_lst = NULL;
	return (status);
}

/*
** create_t_line:
**
** Create a single t_line element, set almost all of his attribute to NULL.
*/

int		create_t_line(t_line **new_line, int position)
{
	if (!(*new_line = (t_line *)malloc(sizeof(t_line))))
		return (MALLOC_ERROR);
	(*new_line)->chars = NULL;
	(*new_line)->next = NULL;
	(*new_line)->position = position;
	return (MALLOC_SUCCESS);
}

/*
** push_end_line:
**
** Extend a t_line element, add a new t_line at the end of the current list.
*/

int		push_end_line(t_line **line_lst)
{
	t_line	*tmp_line;
	
	if (!*line_lst)
		return (create_t_line(line_lst, 0));
	tmp_line = *line_lst;
	while (tmp_line->next)
		tmp_line = tmp_line->next;
	return (create_t_line(&tmp_line->next, tmp_line->position + 1));
}

/*
** is_cursor_last_pos:
**
** Check if the cursor is in the last position of the shell.
*/

int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor)
{
	int		row;

	row = 0;
	while (line_lst->position != cursor->row)
	{
		row++;
		line_lst = line_lst->next;
	}
	return (cursor->column == char_lst_len(line_lst->chars) && 
			cursor->row == row);
}

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
