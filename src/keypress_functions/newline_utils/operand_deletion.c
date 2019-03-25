#include "operand_deletion.h"
#include "t_operand_allocation.h"

/*
** delete_operand:
**
** Give a specific t_operand element to delete into an entire list.
*/

void	delete_operand(t_operand **operand_list, t_operand **to_del)
{
	t_operand	*prev_operand;

	prev_operand = NULL;
	while (*operand_list != *to_del)
	{
		prev_operand = *operand_list;
		operand_list = &(*operand_list)->next;
	}
	if (prev_operand)
			prev_operand->next = (*to_del)->next;
	else
		*operand_list = (*to_del)->next;
	free_operand_node(to_del, 0);
}

/*
** delete_last_operand:
**
** Delete in the chained list the last element. Set up list pointer to NULL if
** there is no more operand.
*/

void	delete_last_operand(t_operand **operand_list)
{
		t_operand *tmp_operand;

		if (!(*operand_list)->next)
		{
			free_operand_node(operand_list, 0);
			return ;
		}
		tmp_operand = *operand_list;
		while (tmp_operand->next->next)
			tmp_operand = tmp_operand->next;
		free_operand_node(&tmp_operand->next, 0);
}

/*
** delete_operand_from:
**
** Free in a t_operand chained list each element from and after a specified \
** starting point.
*/

void	delete_operand_from(t_operand **operand_list, t_operand **from_operand)
{
	if (*operand_list == *from_operand)
		free_operand_lst(operand_list, 0);
	else
	{
		while ((*operand_list)->next != *from_operand)
			operand_list = &(*operand_list)->next;
		free_operand_lst(&(*operand_list)->next, 0);
	}
}
