#include "t_char_utils.h"
#include "t_cursor_utils.h"
#include "t_line_utils.h"

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
** extend_char:
**
** Add a t_char list at the end of an other list.
** Return the position of the junction.
*/

int		extend_char(t_char *old_chars, t_char *char_to_add)
{
	t_char		*start_line;

	start_line = old_chars;
	while (old_chars->next)
		old_chars = old_chars->next;
	old_chars->next = char_to_add;
	update_position(start_line);
	return (old_chars->position + 1);
}


/*
** update_position:
**
** Go from a t_char * to the end of the list to update
** each char position.
*/

void		update_position(t_char *char_lst)
{
	int		index;

	index = 0;
	while (char_lst)
	{
		char_lst->position = index++;
		char_lst = char_lst->next;
	}
}
/*
** free_t_char:
**
** Deallocate a single t_char element, set his pointer to NULL.
*/

void	free_t_char(t_char **char_node)
{
	free(*char_node);
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



/*
** display_chars:
**
** Print on stdout each char of a t_char list.
*/

void		display_chars(t_char *char_lst, t_cursor *cursor, int line, \
		int *printed_cursor)
{
	while (char_lst)
	{
		if (line == cursor->row && cursor->column == char_lst->position)
		{
			*printed_cursor = TRUE;
			show_cursor(char_lst->letter);
		}
		else
			write(1, &char_lst->letter, 1);
		char_lst = char_lst->next;
	}
}

int			char_lst_len(t_char *char_lst)
{
	int		index;

	index = 0;
	while (char_lst)
	{
		index++;
		char_lst = char_lst->next;
	}
	return (index);
}

/*
** get_unlocked_char:
**
** Get the first char in t_char list whom is unlocked.
*/

t_char	*get_unlocked_char(t_char *char_lst)
{
	while (char_lst && char_lst->lock == TRUE)
		char_lst = char_lst->next;
	return (char_lst);
}


/*
** char_lock_len:
**
** Get the len of the blocked part in a t_char
*/

int			char_lock_len(t_char *char_lst)
{
	int		index;

	index = 0;
	while (char_lst && char_lst->lock == TRUE)
	{
		index++;
		char_lst = char_lst->next;
	}
	return (index);
}

