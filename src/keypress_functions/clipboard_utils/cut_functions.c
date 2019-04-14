#include "cut_functions.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"
#include "clipboard.h"
#include "libft.h"
#include "t_char_insert.h"

/*
** line_cut:
**
** Called whenever the user expect to cut the current line.
** Cut the content of the current line and save it inside the
** clipboard_store.
*/

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

/*
** adjust_cursor:
**
** When a word is cutted, check if the new position is valid
** or adjust if it's not the case. In this case, put the cursor
** at the first or last position.
*/

static void	adjust_cursor(t_char *shell_line, t_cursor *cursor)
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

/*
** cut_next_word:
**
** Remove the next word in the current line and save it to the clipboard.
** Select in the first time the current cursor t_char, skip space and move
** until we leave a word.
*/

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
	adjust_cursor(shell_repr->chars, cursor);
	clipboard_store(STORE, &cut);
	return (MALLOC_SUCCESS);
}

/*
** cut_prev_word:
**
** Remove from the shell the previous word of the current line.
** Parse the t_line and store each word beginning in a temporary
** pointer.
** When we reach the pointer t_char, cut the last founded pointer.
*/

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

/*
** paste_clipboard:
**
** Push into the current shell representation the
** local clipped string.
*/

int		paste_clipboard(t_line *shell_repr, t_cursor *cursor)
{
	char	*cut;

	clipboard_store(GET, &cut);
	if (!cut)
		return (SUCCESS);
	while (*cut)
		insert_char(shell_repr, *cut++, cursor);
	return (MALLOC_SUCCESS);
}
