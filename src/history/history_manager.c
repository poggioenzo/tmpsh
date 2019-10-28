/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 13:41:46 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "history_manager.h"
#include "history_adding.h"
#include "history_manager_utils.h"
#include "keyboard.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"

/*
** history_manager:
**
** Analyse the key given to manipulate the history (UP or DOWN key),
** and will behave like expect by the user.
** Check if the current hsitory selection is a keypress repetition,
** delete the old used history if needed and replace it by a new one.
*/

void	history_manager(char *key, t_line *shell_repr, t_cursor *cursor)
{
	static int		is_repetition = FALSE;
	static t_hist	*history = (void *)0;
	t_line			*cursor_line;

	is_repetition = DOWN_KEY(g_last_char) || UP_KEY(g_last_char);
	clean_lastest_history(is_repetition, shell_repr, cursor, history);
	select_current_history(key, &history, is_repetition);
	add_new_history(shell_repr, cursor, history);
	update_line_lst(shell_repr);
	cursor_line = get_cursor_line(shell_repr, cursor);
	cursor->column = char_lst_len(cursor_line->chars);
}
