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

#include "cursor_dependent_selection.h"
#include "cursor_dependent_selection_utils.h"
#include "t_line_utils.h"
#include "char_utils.h"
#include "libft.h"

/*
** get_last_word:
**
** Get the position of the word preceding the cursor.
** Store this information in a t_cursor and/or a t_char element if given.
*/

void		get_last_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char)
{
	t_char		*search_char;
	t_cursor	word_save;

	search_char = NULL;
	research_prev_info(shell_repr, cursor, &word_save, &search_char);
	if (word_cursor)
		ft_memcpy(word_cursor, &word_save, sizeof(t_cursor));
	if (word_char)
	{
		shell_repr = get_cursor_line(shell_repr, word_cursor);
		*word_char = get_cursor_char(word_cursor, shell_repr->chars, NULL);
	}
}

/*
** get_next_word:
**
** Get the position of the word following the cursor.
** Store this information in a t_cursor and/or a t_char element if given.
*/

void		get_next_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char)
{
	t_char	*search_char;
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	search_char = get_cursor_char(cursor, cursor_line->chars, NULL);
	while (search_char && ft_isalnum(search_char->letter))
		search_char = search_char->next;
	skip_empty_char(&cursor_line, &search_char);
	if (word_char)
		*word_char = search_char;
	if (cursor_line && word_cursor)
	{
		word_cursor->column = search_char->position;
		word_cursor->row = cursor_line->position;
	}
	else if (!cursor_line && word_cursor)
		set_last_pos(shell_repr, word_cursor);
}

/*
** get_cursor_line:
**
** Get the line where the cursor is present.
*/

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor)
{
	while (shell_lines->position != cursor->row)
		shell_lines = shell_lines->next;
	return (shell_lines);
}

/*
** get_prev_cursor_line:
**
** Get the t_line before the cursor row position
*/

t_line		*get_prev_cursor_line(t_cursor *cursor, t_line *shell_repr)
{
	if (cursor->row == 0)
		return (NULL);
	while (shell_repr->next->position != cursor->row)
		shell_repr = shell_repr->next;
	return (shell_repr);
}

/*
** get_cursor_char:
**
** Get the t_char * element corresponding to the selected cursor.
** Get also the previous t_char if @t_char **prev_char is not NULL.
** If the cursor it at the last position, return NULL.
*/

t_char		*get_cursor_char(t_cursor *cursor, t_char *char_lst,\
		t_char **prev_char)
{
	t_char	*cursor_char;

	if (prev_char)
		*prev_char = NULL;
	cursor_char = char_lst;
	while (cursor_char && cursor_char->position != cursor->column)
	{
		if (prev_char)
			*prev_char = cursor_char;
		cursor_char = cursor_char->next;
	}
	return (cursor_char);
}
