/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "t_char_utils.h"

/*
** extend_char:
**
** Add a t_char list at the end of an other list.
** Return the position of the junction to update cursor position.
*/

int			extend_char(t_char *prev_chars, t_char *char_to_add)
{
	t_char		*start_line;

	start_line = prev_chars;
	while (prev_chars->next)
		prev_chars = prev_chars->next;
	prev_chars->next = char_to_add;
	update_position(start_line);
	return (prev_chars->position + 1);
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
** increment_char_end:
**
** Incrementing the end of a t_char line from 1
** starting from the given t_char position.
*/

void		increment_char_end(t_char *char_lst)
{
	int reference_pos;

	reference_pos = char_lst->position;
	while (char_lst)
	{
		char_lst->position = reference_pos++;
		char_lst = char_lst->next;
	}
}

/*
** char_lst_len:
**
** Get the total length of a t_char chained list.
*/

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
