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

#include "standard_move.h"
#include "cursor_dependent_selection.h"
#include "char_utils.h"

/*
** move_left:
**
** Check if the cursor can be moved to the left position,
** decrementing the cursor if it's possible.
*/

void			move_left(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*prev_char;
	t_line	*cursor_line;
	t_line	*prev_line;

	prev_line = get_prev_cursor_line(cursor, shell_repr);
	cursor_line = prev_line ? prev_line->next : shell_repr;
	get_cursor_char(cursor, cursor_line->chars, &prev_char);
	if (prev_char->lock == FALSE)
		cursor->column--;
	else if (prev_line)
	{
		cursor->row--;
		cursor->column = char_lst_len(prev_line->chars);
	}
}

/*
** move_right:
**
** Check if the cursor can be moved to the left position,
** decrementing the cursor if it's possible.
*/

void			move_right(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*prev_char;

	shell_repr = get_cursor_line(shell_repr, cursor);
	if (get_cursor_char(cursor, shell_repr->chars, &prev_char))
		cursor->column++;
	else if (shell_repr->next)
	{
		cursor->row++;
		cursor->column = char_lock_len(shell_repr->next->chars);
	}
}

/*
** cursor_calibration:
**
** Whenever the cursor is moved up or down, set his column position
** depending of the t_char list configuration.
*/

static void		cursor_calibration(t_char *char_lst, t_cursor *cursor)
{
	int		line_len;
	int		lock_len;

	lock_len = char_lock_len(char_lst);
	line_len = char_lst_len(char_lst);
	if (cursor->column > line_len)
		cursor->column = line_len;
	else if (lock_len > cursor->column)
		cursor->column = lock_len;
}

/*
** move_down:
**
** Move down the cursor if it is allowed.
** Recalculate the cursor->column position if needed.
*/

void			move_down(t_line *shell_repr, t_cursor *cursor)
{
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	if (!cursor_line->next)
		return ;
	cursor->row++;
	cursor_line = cursor_line->next;
	cursor_calibration(cursor_line->chars, cursor);
}

/*
** move_up:
**
** Move up the cursor if it is allowed.
** Recalculate the cursor->column position if needed.
*/

void			move_up(t_line *shell_repr, t_cursor *cursor)
{
	t_line		*cursor_line;

	if (cursor->row == 0)
		return ;
	cursor->row--;
	cursor_line = get_cursor_line(shell_repr, cursor);
	cursor_calibration(cursor_line->chars, cursor);
	return ;
}
