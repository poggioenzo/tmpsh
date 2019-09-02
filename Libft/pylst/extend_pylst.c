#include "libft.h"

/*
** extend_pylst:
**
** Add a pylst to an other pylst.
*/

void	extend_pylst(t_pylst **start, t_pylst *end, int deep_cpy)
{
	t_pylst		*end_cpy;

	if (!*start && !end)
		return ;
	end_cpy = deep_cpy ? pylst_deepcpy(end) : pylst_shacpy(end);
	while (*start && (*start)->next)
		start = &(*start)->next;
	if (!*start)
		*start = end_cpy;
	else
		(*start)->next = end_cpy;
}
