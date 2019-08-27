#include "t_line_allocation.h"
#include "char_utils.h"
#include "libft.h"

/*
** free_t_line:
**
** Free a single t_line element.
*/

int			free_t_line(t_line **line_lst, int status)
{
	t_char		*char_lst;

	char_lst = (*line_lst)->chars;
	free_t_char_lst(&char_lst, status);
	FREE(*line_lst);
	*line_lst = NULL;
	return (status);
}

/*
** free_t_line_lst:
**
** Free the entire chained list of t_line.
*/

int			free_t_line_lst(t_line **line_lst, int status)
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

void		create_t_line(t_line **new_line, int position)
{
	if (!(*new_line = (t_line *)MALLOC(sizeof(t_line))))
		exit(-1);
	(*new_line)->chars = NULL;
	(*new_line)->next = NULL;
	(*new_line)->position = position;
}

/*
** push_end_line:
**
** Extend a t_line element, add a new t_line at the end of the current list.
*/

void		push_end_line(t_line **line_lst)
{
	t_line	*tmp_line;

	if (!*line_lst)
		create_t_line(line_lst, 0);
	else
	{
		tmp_line = *line_lst;
		while (tmp_line->next)
			tmp_line = tmp_line->next;
		create_t_line(&tmp_line->next, tmp_line->position + 1);
	}
}
