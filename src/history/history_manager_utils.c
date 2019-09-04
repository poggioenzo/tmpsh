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

#include "history_manager_utils.h"
#include "keyboard.h"
#include "line_utils.h"
#include "cursor_dependent_selection.h"
#include "history_store.h"
#include "libft.h"

/*
** get_last_history_node:
**
** Set up the given t_hist ** to the last element of the
** chained list;
*/

static void	get_last_history_node(t_hist **history)
{
	t_hist	*tmp_hist;

	if (!*history)
		return ;
	tmp_hist = *history;
	while (tmp_hist->next)
		tmp_hist = tmp_hist->next;
	*history = tmp_hist;
}

/*
** del_extra_lines:
**
** Cut extra lines if the lastest history was on multiple lines.
*/

static void	del_extra_lines(t_line *cursor_line, int line_to_del)
{
	while (line_to_del > 0)
	{
		extract_line(cursor_line, cursor_line->next);
		line_to_del--;
	}
}

/*
** clean_lastest_history:
**
** Remove each lines used by the previous history (or the current edited
** line).
*/

void		clean_lastest_history(int is_repetition, t_line *shell_repr,\
		t_cursor *cursor, t_hist *curr_history)
{
	int		used_lines;
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	line_proper(cursor_line);
	if (is_repetition && curr_history)
	{
		used_lines = ft_strcount(curr_history->line, '\n');
		del_extra_lines(cursor_line, used_lines);
	}
}

/*
** try_reset_history:
**
** Whenever the current history is NULL, select the right element
** according to the fact that the current history call is a repetition
** or depending of the previous pressed key.
*/

static void	try_reset_history(char *key, t_hist **history, int is_repetition)
{
	history_store(GET, history);
	if (!*history)
		return ;
	if (is_repetition == FALSE && UP_KEY(key))
		get_last_history_node(history);
	else if (is_repetition == FALSE && DOWN_KEY(key))
		*history = NULL;
	else if (is_repetition == TRUE)
	{
		if (DOWN_KEY(g_last_char) && UP_KEY(key))
			get_last_history_node(history);
		else if (!(UP_KEY(g_last_char) && DOWN_KEY(key)))
			*history = NULL;
	}
}

/*
** select_current_history:
**
** Manipulate the t_hist static variable which is pointing to the
** local history according to the pressed key.
*/

void		select_current_history(char *key, t_hist **history, \
		int is_repetition)
{
	if (is_repetition == FALSE)
		*history = NULL;
	if (*history == NULL)
	{
		try_reset_history(key, history, is_repetition);
		return ;
	}
	if (DOWN_KEY(key))
		*history = (*history)->next;
	else if (UP_KEY(key) && (*history)->prev)
		*history = (*history)->prev;
}
