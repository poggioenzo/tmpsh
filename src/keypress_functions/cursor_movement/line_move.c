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

#include "line_move.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"

/*
** start_line:
**
** Set the cursor to the beginning of his current line
*/

void		start_line(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_cursor_line(shell_repr, cursor);
	cursor->column = char_lock_len(shell_repr->chars);
}

/*
** end_line:
**
** Set the cursor to the beginning of his current line
*/

void		end_line(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_cursor_line(shell_repr, cursor);
	cursor->column = char_lst_len(shell_repr->chars);
}
