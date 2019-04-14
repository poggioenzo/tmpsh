#include "t_char_allocation.h"
#include "libft.h"

/*
** create_char:
**
** Allocate a single t_char element.
*/

int	create_char(t_char	**char_node, char letter, int position, int lock)
{
	if (!(*char_node = (t_char *)malloc(sizeof(t_char))))
		return (MALLOC_ERROR);
	(*char_node)->letter = letter;
	(*char_node)->position = position;
	(*char_node)->next = NULL;
	(*char_node)->lock = lock;
	return (MALLOC_SUCCESS);
}

/*
** push_end_char:
**
** Create at the end of the t_char * chained list a new t_char element.
*/

int			push_end_char(t_char **char_node, char letter, int lock)
{
	t_char	*tmp_char;

	if (!*char_node)
		 return (create_char(char_node, letter, 0, lock));
	tmp_char = *char_node;
	while (tmp_char->next)
		tmp_char = tmp_char->next;
	if (create_char(&tmp_char->next, letter, tmp_char->position + 1, lock) \
			== MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (MALLOC_SUCCESS);
}

/*
** free_t_char:
**
** Deallocate a single t_char element, set his pointer to NULL.
*/

void	free_t_char(t_char **char_node)
{
	FREE(*char_node);
	*char_node = NULL;
}

/*
** free_t_char_lst:
**
** Free an entire chained list of t_char, and set his pointer to NULL.
** Return the given status value.
*/

int			free_t_char_lst(t_char **char_lst, int status)
{
	t_char	*tmp_char;
	t_char	*next_char;

	tmp_char = *char_lst;
	while (tmp_char)
	{
		next_char = tmp_char->next;
		free_t_char(&tmp_char);
		tmp_char = next_char;
	}
	*char_lst = NULL;
	return (status);
}
