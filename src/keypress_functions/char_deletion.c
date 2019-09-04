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

#include "char_deletion.h"
#include "char_utils.h"
#include "line_utils.h"
#include "cursor_dependent_selection.h"

/*
** join_end_of_line:
**
** Whenever a line is deleted, try to move the char at the end of the
** deleted string to the upper line.
*/

static void		join_end_of_line(t_char *prev_chars, t_char *cursor_chars, \
		t_cursor *cursor)
{
	t_char	*last_cursor_lock;

	last_cursor_lock = NULL;
	while (cursor_chars && cursor_chars->lock == TRUE)
	{
		last_cursor_lock = cursor_chars;
		cursor_chars = cursor_chars->next;
	}
	cursor->column = extend_char(prev_chars, cursor_chars);
	last_cursor_lock->next = NULL;
}

/*
** delete_line:
**
** Perform line deletion whenever whe are try to delete the beginning of
** a t_line.
** Add to the end of the upper string the content of the deleted string.
*/

static void		delete_line(t_line *shell_repr, int position, t_cursor *cursor)
{
	t_line	*prev_line;
	t_line	*cursor_line;

	if (position == 0)
		return ;
	prev_line = NULL;
	cursor_line = shell_repr;
	while (cursor_line && cursor_line->position != position)
	{
		prev_line = cursor_line;
		cursor_line = cursor_line->next;
	}
	join_end_of_line(prev_line->chars, cursor_line->chars, cursor);
	prev_line->next = cursor_line->next;
	cursor->row--;
	free_t_line(&cursor_line, 0);
	update_line_lst(shell_repr);
}

/*
** del_pos_char:
**
** Delete a char according to the cursor position.
** Avoid deletion of the first line.
** If the char that who try to be deleted if is a locked char,
** try to delete the current line.
*/

static int		del_pos_char(t_char **char_lst, t_cursor *cursor)
{
	t_char	*prev_char;
	t_char	*curr_char;

	if (cursor->column == 0)
		return (deletion_succeed);
	curr_char = *char_lst;
	prev_char = NULL;
	while (curr_char && curr_char->position + 1 != cursor->column)
	{
		prev_char = curr_char;
		curr_char = curr_char->next;
	}
	if (curr_char->lock == TRUE)
		return (del_line);
	else if (!prev_char)
		*char_lst = curr_char->next;
	else
		prev_char->next = curr_char->next;
	update_position(*char_lst);
	free_t_char(&curr_char);
	cursor->column--;
	return (deletion_succeed);
}

/*
** delete_char:
**
** Try to delete the char at the cursor position,
** try to delete the current line if needed.
*/

void			delete_char(t_line *shell_repr, t_cursor *cursor)
{
	int		status;
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	status = del_pos_char(&cursor_line->chars, cursor);
	if (status == del_line)
		delete_line(shell_repr, cursor_line->position, cursor);
}
