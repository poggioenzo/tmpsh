#include "t_bracket_utils.h"
#include "newline_keypress.h"
#include <stdlib.h>

/*
** create_operand:
**
** Allocate a single t_operand element and set up his attribute.
*/

int		create_operand(t_operand **operand, int type, char open_char)
{
	if (!(*operand = (t_operand *)malloc(sizeof(t_operand))))
			return (MALLOC_ERROR);
	(*operand)->open_char = open_char;
	(*operand)->type = type;
	(*operand)->next = NULL;
	return (MALLOC_SUCCESS);
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

int		push_operand(t_operand **operand_list, int type, char open_char)
{
	if (!*operand_list)
			return (create_operand(operand_list, type, open_char));
	while ((*operand_list)->next)
			operand_list = &(*operand_list)->next;
	return (create_operand(&(*operand_list)->next, type, open_char));

}

/*
** free_operand_node:
**
** Free a single t_operand element and set his pointer to NULL.
** Return the status value.
*/

int		free_operand_node(t_operand **operand_node, int status)
{
	free(*operand_node);
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


/*
** get_last_bracket:
**
** From a given t_operand list, search the last opening bracket element,
** which are not a seperator.
**
*/

t_operand	*get_last_bracket(t_operand *operand_list)
{
	t_operand *last_open;

	last_open = NULL;
	while (operand_list)
	{
		if (!(operand_list->type & SEPARATOR))
				last_open = operand_list;
		operand_list = operand_list->next;
	}
	return (last_open);
}

