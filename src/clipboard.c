#include "clipboard.h"
#include "cursor_dependent_selection.h"
#include "char_utils.h"
#include "t_char_insert.h"
#include "keyboard.h"
#include "libft.h"
#include "cursor_move.h"

void	clipboard_store(int action, char **clipped_str)
{
	static char		*cutted_str = NULL;

	if (action == STORE)
		cutted_str = *clipped_str;
	else if (action == GET)
		*clipped_str = cutted_str;
	else if (action == FREE)
		ft_strdel(&cutted_str);

}

int		line_cut(t_line	*shell_repr, t_cursor *cursor)
{
	t_line	*cursor_line;
	char	*cut = NULL;

	cursor_line = get_cursor_line(shell_repr, cursor);
	cut = delete_char_range(cursor_line->chars, NULL, NULL, TRUE);
	if (!cut)
		return (MALLOC_ERROR);
	else if (!*cut)
		return (ft_strdel_out(&cut, MALLOC_SUCCESS));
	cursor->column = char_lst_len(cursor_line->chars);
	clipboard_store(STORE, &cut);
	return (MALLOC_SUCCESS);
}

void	adjust_cursor(t_char *shell_line, t_cursor *cursor)
{
	t_char	*unlocked;
	int		lst_len;

	cursor->column--;
	lst_len = char_lst_len(shell_line);
	unlocked = get_unlocked_char(shell_line);
	if (!unlocked || cursor->column > lst_len)
		cursor->column = lst_len;
	else if (cursor->column < unlocked->position)
		cursor->column = unlocked->position;
}

int		cut_next_word(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*word_end;
	t_char	*cursor_char;
	char	*cut;

	shell_repr = get_cursor_line(shell_repr, cursor);
	cursor_char = get_cursor_char_only(shell_repr->chars, cursor);
	if (!cursor_char)
		return (MALLOC_SUCCESS);
	word_end = cursor_char;
	while (word_end && ft_isspace(word_end->letter))
		word_end = word_end->next;
	while (word_end && word_end->next && !ft_isspace(word_end->letter))
		word_end = word_end->next;
	cut = delete_char_range(shell_repr->chars, cursor_char, word_end, TRUE);
	if (!cut)
		return (MALLOC_ERROR);
	ft_dprintf(fd_debug, "cursor : (%d, %d)\n", cursor->row, cursor->column);
	adjust_cursor(shell_repr->chars, cursor);
	ft_dprintf(fd_debug, "cursor AFTER: (%d, %d)\n", cursor->row, cursor->column);
	clipboard_store(STORE, &cut);
	return (MALLOC_SUCCESS);
}

int		cut_prev_word(t_line *shell_repr, t_cursor *cursor)
{
	t_char	*last_word;
	t_char	*tmp_char;
	int		in_word;
	char	*cut;

	shell_repr = get_cursor_line(shell_repr, cursor);
	tmp_char = get_unlocked_char(shell_repr->chars);
	if (!tmp_char)
		return (MALLOC_SUCCESS);
	in_word = FALSE;
	last_word = tmp_char;
	while (tmp_char && tmp_char->position <= cursor->column)
	{
		if (in_word == FALSE && !ft_isspace(tmp_char->letter))
		{
			in_word = TRUE;
			last_word = tmp_char;
		}
		else if (in_word == TRUE && ft_isspace(tmp_char->letter))
			in_word = FALSE;
		tmp_char = tmp_char->next;
	}
	cursor->column = last_word ? last_word->position + 1 : 0;
	adjust_cursor(shell_repr->chars, cursor);
	if (!(cut = delete_char_range(shell_repr->chars, last_word, tmp_char, TRUE)))
		return (MALLOC_ERROR);

	clipboard_store(STORE, &cut);
	return (MALLOC_SUCCESS);
}

int		paste_clipboard(t_line *shell_repr, t_cursor *cursor)
{
	char	*cut;

	clipboard_store(GET, &cut);
	if (!cut)
		return (SUCCESS);
	while (*cut)
	{
		if (insert_char(shell_repr, *cut++, cursor) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (MALLOC_SUCCESS);
}

int		is_clipoard_key(char *key)
{
	return (CTRL_W(key) || CTRL_N(key) || CTRL_L(key) || CTRL_P(key));
}

int		clipoard_manager(char *key, t_line *shell_repr, t_cursor *cursor)
{
	if (CTRL_W(key))
		return (cut_prev_word(shell_repr, cursor));
	else if (CTRL_N(key))
		return (cut_next_word(shell_repr, cursor));
	else if (CTRL_L(key))
		return (line_cut(shell_repr, cursor));
	else if (CTRL_P(key))
		return (paste_clipboard(shell_repr, cursor));
	return (MALLOC_SUCCESS);
}









