#include "t_operand_allocation.h"
#include "libft.h"

/*
** create_operand:
**
** Allocate a single t_operand element and set up his attribute.
*/

void	create_operand(t_operand **operand, int type, char open_char)
{
	if (!(*operand = (t_operand *)MALLOC(sizeof(t_operand))))
			exit(-1);
	(*operand)->open_char = open_char;
	(*operand)->type = type;
	(*operand)->next = NULL;
}

/*
** push_operand:
**
** Add at the end of the current list a new t_operand element,
** or create a new list if the pointer is NULL.
**
** return value:
** - return MALLOC_SUCCESS if the allocation succes, MALLOC_ERROR otherwise
*/

void		push_operand(t_operand **operand_list, int type, char open_char)
{
	if (!*operand_list)
			create_operand(operand_list, type, open_char);
	else
	{
		while ((*operand_list)->next)
				operand_list = &(*operand_list)->next;
		create_operand(&(*operand_list)->next, type, open_char);
	}
}

/*
** free_operand_node:
**
** Free a single t_operand element and set his pointer to NULL.
** Return the status value.
*/

int		free_operand_node(t_operand **operand_node, int status)
{
	FREE(*operand_node);
	*operand_node = NULL;
	return (status);
}

/*
** free_operand_lst:
**
** Go through each element of a t_operand list and free each element.
** Set the list pointer to NULL and return status value.
*/

int		free_operand_lst(t_operand **operand_list, int status)
{
	t_operand *tmp_operand;
	t_operand *next_operand;

	tmp_operand = *operand_list;
	while (tmp_operand)
	{
		next_operand = tmp_operand->next;
		free_operand_node(&tmp_operand, 0);
		tmp_operand = next_operand;
	}
	*operand_list = NULL;
	return (status);
}
