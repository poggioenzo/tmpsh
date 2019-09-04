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

#include "tmpsh.h"
#include "libft.h"
#include "t_line_utils.h"
#include "char_utils.h"

/*
** is_cursor_pos:
**
** Condition to check according to a t_line and a t_char if we are on
** the cursor position.
*/

static int	is_cursor_pos(t_line *shell_repr, t_char *char_lst, \
		t_cursor *cursor)
{
	return (shell_repr->position == cursor->row && \
			char_lst->position == cursor->column);
}

/*
** research_prev_info:
**
** Parse the entire shell representation from the first char
** until the cursor position to get the cursor's previous char.
** Whenever a new word start is found, store his position.
*/

void		research_prev_info(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **search_char)
{
	int in_word;

	in_word = FALSE;
	word_cursor->row = 0;
	word_cursor->column = char_lock_len(shell_repr->chars);
	while (shell_repr && shell_repr->position <= cursor->row)
	{
		*search_char = get_unlocked_char(shell_repr->chars);
		while (*search_char && !is_cursor_pos(shell_repr, *search_char, cursor))
		{
			if (ft_isalnum((*search_char)->letter) && in_word == FALSE)
			{
				in_word = TRUE;
				word_cursor->row = shell_repr->position;
				word_cursor->column = (*search_char)->position;
			}
			else if (ft_isspace((*search_char)->letter) && in_word)
				in_word = FALSE;
			*search_char = (*search_char)->next;
		}
		in_word = FALSE;
		shell_repr = shell_repr->next;
	}
}

/*
** set_last_pos:
**
** Set up to the cursor the last avaible position of the shell.
*/

void		set_last_pos(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_last_line(shell_repr);
	cursor->row = shell_repr->position;
	cursor->column = char_lst_len(shell_repr->chars);
}

/*
** skip_empty_char:
**
** Skip all carachters which are not newline.
*/

void		skip_empty_char(t_line **cursor_line, t_char **search_char)
{
	while (*cursor_line)
	{
		while (*search_char && !ft_isalnum((*search_char)->letter))
			*search_char = (*search_char)->next;
		if (*search_char)
			break ;
		*cursor_line = (*cursor_line)->next;
		if (*cursor_line)
			*search_char = get_unlocked_char((*cursor_line)->chars);
	}
}
