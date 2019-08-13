#include "t_hist_allocation.h"
#include "libft.h"

/*
** create_t_hist:
**
** Allocate a single t_hist element, filling up his field.
*/

static void		create_t_hist(t_hist **hist_node, t_hist *prev, char *content,
		int is_tmp)
{
	*hist_node = (t_hist *)ft_memalloc(sizeof(t_hist));
	(*hist_node)->line = content;
	(*hist_node)->next = NULL;
	(*hist_node)->prev = prev;
	(*hist_node)->is_tmp = is_tmp;
}

/*
** pust_t_hist:
**
** Add to the t_hist chained list a new node.
** Push it at the end of our list.
*/

void	push_t_hist(t_hist **history, char *content, int is_tmp)
{
	t_hist	*curr_node;

	if (!*history)
		create_t_hist(history, NULL, content, is_tmp);
	else
	{
		curr_node = *history;
		while (curr_node->next)
			curr_node = curr_node->next;
		create_t_hist(&curr_node->next, curr_node, content, is_tmp);
	}
}

/*
** free_history_node:
**
** Free a single element of t_hist.
*/

static void	free_history_node(t_hist **hist_node)
{
	FREE((*hist_node)->line);
	FREE(*hist_node);
	*hist_node = NULL;
}

/*
** free_history:
**
** Free an entire chained list of t_hist elements.
** Setting up his pointer to NULL, and returning status.
*/

int		free_history(t_hist **history, int status)
{
	t_hist		*tmp_node;
	t_hist		*next_node;

	tmp_node = *history;
	while (tmp_node)
	{
		next_node = tmp_node->next;
		free_history_node(&tmp_node);
		tmp_node = next_node;
	}
	*history = NULL;
	return (status);
}
