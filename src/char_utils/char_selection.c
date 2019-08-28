#include "char_selection.h"

/*
** get_unlocked_char:
**
** Return:
** First unlocked t_char of the list,
** NULL otherwise.
*/

t_char		*get_unlocked_char(t_char *char_lst)
{
	while (char_lst && char_lst->lock == TRUE)
		char_lst = char_lst->next;
	return (char_lst);
}

/*
** get_last_lock:
**
** Return the last locked element in a t_char list.
*/

void		get_last_lock(t_char *char_lst, t_char **last_lock)
{
	while (char_lst->next && char_lst->next->lock == TRUE)
		char_lst = char_lst->next;
	*last_lock = char_lst;
}

/*
** get_last_char:
**
** Return the last t_char list which is unlocked,
** set to NULL **last_char if all is locked.
*/

void		get_last_char(t_char *char_lst, t_char **last_char)
{
	while (char_lst && (char_lst->lock == TRUE || char_lst->next))
		char_lst = char_lst->next;
	*last_char = char_lst;
}

/*
** search_prev_char:
**
** Search a the char who is preceding a specific pointer (from).
*/

void		search_prev_char(t_char *char_lst, t_char **prev_char,\
				t_char *from)
{
	*prev_char = char_lst;
	while ((*prev_char)->next != from)
		*prev_char = (*prev_char)->next;
}
