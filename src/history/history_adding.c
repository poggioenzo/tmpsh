#include "history_adding.h"
#include "char_utils.h"
#include "line_utils.h"
#include "t_char_insert.h"
#include "libft.h"

/*
** prepare_hist_t_line:
**
** Prepare the t_line element in which we will add our
** command line.
*/

static void		prepare_hist_t_line(t_line **line_to_create)
{
	create_t_line(line_to_create, 0);
	insert_string(&(*line_to_create)->chars, "> ", TRUE);
}

/*
** convert_char:
**
** Convert each char of a string into a t_char chained list,
** only to the end of the string or to a newline.
** Allocate a new line if it's needed.
*/

static void		convert_char(char *history_line, t_line **line_to_fill)
{
	if (!*line_to_fill)
		prepare_hist_t_line(line_to_fill);
	while (*history_line && *history_line != '\n')
		push_end_char(&(*line_to_fill)->chars, *history_line++, FALSE);
}

/*
** add_new_history:
**
** Add each line of the new history into the t_line chained list.
** Append in a first time the first line, and loop over each newline
** to create different t_list node.
*/

void			add_new_history(t_line *shell_repr, t_cursor *cursor, \
		t_hist *history)
{
	t_line	*cursor_line;
	char	*hist_line;
	t_line	*followed_save;

	cursor_line = get_cursor_line(shell_repr, cursor);
	followed_save = cursor_line->next;
	hist_line = history ? history->line : "\0";
	convert_char(hist_line, &cursor_line);
	if (!history)
		return ;
	cursor_line->next = NULL;
	while ((hist_line = ft_strchr(hist_line, '\n')))
	{
		hist_line++;
		convert_char(hist_line, &cursor_line->next);
		cursor_line = cursor_line->next;
	}
	cursor_line->next = followed_save;
	update_line_lst(shell_repr);
}
