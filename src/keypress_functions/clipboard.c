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

#include "clipboard.h"
#include "keyboard.h"
#include "libft.h"
#include "cursor_move.h"
#include "cut_functions.h"

/*
** clipboard_store:
**
** Manager function to keep address of the local clipped string.
**
** Available action:
**
** - GET to get the current clipped string.
** - STORE to save the clipped string.
** - GO_FREE to free the clipped string.
*/

void	clipboard_store(int action, char **clipped_str)
{
	static char		*cutted_str = NULL;

	if (action == STORE)
	{
		ft_strdel(&cutted_str);
		cutted_str = *clipped_str;
	}
	else if (action == GET)
		*clipped_str = cutted_str;
	else if (action == GO_FREE)
		ft_strdel(&cutted_str);
}

/*
** is_clipoard_key:
**
** Check if the given key is one of the clipboard system.
*/

int		is_clipoard_key(char *key)
{
	return (CTRL_W(key) || CTRL_N(key) || CTRL_L(key) || CTRL_P(key));
}

/*
** clipoard_manager:
**
** Use a given key from the keyboard and call the expected function
** according to this key.
*/

void	clipoard_manager(char *key, t_line *shell_repr, t_cursor *cursor)
{
	if (CTRL_W(key))
		cut_prev_word(shell_repr, cursor);
	else if (CTRL_N(key))
		cut_next_word(shell_repr, cursor);
	else if (CTRL_L(key))
		line_cut(shell_repr, cursor);
	else if (CTRL_P(key))
		paste_clipboard(shell_repr, cursor);
}
