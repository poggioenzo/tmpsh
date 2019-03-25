#include "history_manager.h"
#include "history_adding.h"
#include "history_manager_utils.h"
#include "keyboard.h"
#include "char_utils.h"
#include "cursor_dependent_selection.h"


/*
** check_last_key:
**
** Analyse the previous typed char to check if the current history
** selection is a repetition. If it a new history usage, set up the
** history pointer to the last node of the chained list.
*/

static void	check_last_key(int *is_repetition)
{
	if (DOWN_KEY(g_last_char) || UP_KEY(g_last_char))
        *is_repetition = TRUE;
	else
		*is_repetition = FALSE;
}

/*
** history_manger:
**
** Analyse the key given to manipulate the history (UP or DOWN key),
** and will behave like expect by the user.
** Check if the current hsitory selection is a keypress repetition,
** delete the old used history if needed and replace it by a new one.
**
** return value:
** - SUCCESS if all happend properly, MALLOC_ERROR if an allocation
** failed during the process.
*/

int		history_manager(char *key, t_line *shell_repr, t_cursor *cursor)
{
	static int	    is_repetition = FALSE;
	static t_hist	*history = (void *) 0;
    t_line          *cursor_line;

	check_last_key(&is_repetition);
    clean_lastest_history(is_repetition, shell_repr, cursor, history);
    select_current_history(key, &history, is_repetition);
    if (add_new_history(shell_repr, cursor, history) == MALLOC_ERROR)
		return (MALLOC_ERROR);
    cursor_line = get_cursor_line(shell_repr, cursor);
    cursor->column = char_lst_len(cursor_line->chars);
	return (SUCCESS);
}
