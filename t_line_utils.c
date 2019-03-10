#include "t_line_utils.h"

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
	(*new_line)->prev = prev;
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


