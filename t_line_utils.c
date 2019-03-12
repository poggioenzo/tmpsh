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

int		create_t_line(t_line **new_line, t_line *prev, int position)
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
		return (create_t_line(line_lst, NULL, 0));
	tmp_line = *line_lst;
	while (tmp_line->next)
		tmp_line = tmp_line->next;
	return (create_t_line(&tmp_line->next, tmp_line, tmp_line->position + 1));
}

/*
** is_cursor_last_pos:
**
** Check if the cursor is in the last position of the shell.
*/

int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor)
{
	t_char	*char_lst;
	int		row;

	row = 0;
	while (line_lst->next)
	{
		row++;
		line_lst = line_lst->next;
	}
	return (cursor->column == char_lst_len(line_lst->chars) && 
			cursor->row == row);
}

/*
** get_cursor_line:
**
** Get the line where the cursor is present.
*/

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor)
{
	while (shell_lines->position != cursor->row)
		shell_lines = shell_lines->next;
	return (shell_lines);
}

void		DEBUG_print_line(t_line *shell_lines, int fd)
{
	t_char	*char_lst;

	while (shell_lines)
	{
		char_lst = shell_lines->chars;
		ft_dprintf(fd, "%d =>", shell_lines->position);
		while (char_lst)
		{
			ft_dprintf(fd, "(%c, %d, %d)-->", char_lst->letter, char_lst->position,
					char_lst->lock);
			char_lst = char_lst->next;
		}
		ft_dprintf(fd, "NULL\n");
		shell_lines = shell_lines->next;
	}
}

