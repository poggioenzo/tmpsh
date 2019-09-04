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

#include "cursor_move.h"
#include "keyboard.h"
#include "line_move.h"
#include "standard_move.h"
#include "word_move.h"

/*
** is_key_movement:
**
** Check if the given key corresponding to a cursor control touch
*/

int			is_key_movement(char *key)
{
	return (LEFT_KEY(key) || RIGHT_KEY(key) || MOVE_UP(key) \
			|| MOVE_DOWN(key) || HOME(key) || END(key) || CTRL_A(key) || \
			CTRL_E(key) || PREV_WORD(key) || NEXT_WORD(key));
}

/*
** simple_cursor_move:
**
** Manage, depending of the pressed key, where the cursor have to be move.
*/

void		simple_cursor_move(t_line *shell_repr, char *key, t_cursor *cursor)
{
	if (LEFT_KEY(key))
		move_left(shell_repr, cursor);
	else if (RIGHT_KEY(key))
		move_right(shell_repr, cursor);
	else if (MOVE_UP(key))
		move_up(shell_repr, cursor);
	else if (MOVE_DOWN(key))
		move_down(shell_repr, cursor);
	else if (HOME(key) || CTRL_A(key))
		start_line(shell_repr, cursor);
	else if (END(key) || CTRL_E(key))
		end_line(shell_repr, cursor);
	else if (PREV_WORD(key))
		previous_word(shell_repr, cursor);
	else if (NEXT_WORD(key))
		next_word(shell_repr, cursor);
}
