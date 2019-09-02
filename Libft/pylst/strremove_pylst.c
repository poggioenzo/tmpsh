#include "libft.h"

/*
** strremove_pylst:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Like remove_pylst, but use a char * as value.
*/

void	strremove_pylst(t_pylst **pylst, char *value)
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *pylst;
	while (curr && !ft_strequ(value, curr->value))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*pylst = (*pylst)->next;
	else
		prev->next = curr->next;
	free_pylst_node(&curr, 0);
}
