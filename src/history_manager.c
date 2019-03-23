#include "history_manager.h"
#include "history.h"
#include "t_char_utils.h"
#include "t_char_insert.h"
#include "t_line_utils.h"
#include "cursor_move.h"
#include "libft.h"

/*
** history_store:
**
** Function to manage the memory of the t_hist chained list,
** from his creation to his deletion.
** Avaible action : CREATE, GET or FREE
**
** - CREATE : Store the current HISTORY_FILE into a chained list format,
**            giving also the pointer to history.
** - GET : Give the capacity to get the current allocated history.
** - FREE : Free the space allocated to the t_hist chained list.
** - STORE : Register the new history in the store.
*/

int		history_store(int action, t_hist **history)
{
	static t_hist	*saved_history;

	if (action == CREATE)
	{
		if (store_history(history) == FAILURE)
			return (FAILURE);
		saved_history = *history;
	}
	else if (action == STORE)
		saved_history = *history;
	else if (action == GET)
		*history = saved_history;
	else if (action == FREE)
		free_history(&saved_history, 0);
	return (SUCCESS);
}



/*
** get_last_history_node:
**
** Set up the given t_hist ** to the last element of the
** chained list;
*/

static void    get_last_history_node(t_hist **history)
{
    t_hist  *tmp_hist;

    if (!*history)
        return ;
    tmp_hist = *history;
    while (tmp_hist->next)
        tmp_hist = tmp_hist->next;
    *history = tmp_hist;
}

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
** line_proper:
**
** Use to clean up the line wherever the cursor is positionned.
** Delete the unlocked part of a t_char list.
*/

static void    line_proper(t_line *cursor_line)
{
    t_char  *char_lst;

    char_lst = cursor_line->chars;
    while (char_lst->next && char_lst->next->lock == TRUE)
        char_lst = char_lst->next;
    free_t_char_lst(&char_lst->next, 0);
}

/*
** del_extra_lines:
**
** Cut extra lines if the lastest history was on multiple lines.
*/

static void            del_extra_lines(t_line *cursor_line, int line_to_del)
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

static void    clean_lastest_history(int is_repetition, t_line *shell_repr, \
        t_cursor *cursor, t_hist *curr_history)
{
    int     used_lines;
    t_line  *cursor_line;
    
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

static void    try_reset_history(char *key, t_hist **history, int is_repetition)
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

static void    select_current_history(char *key, t_hist **history, int is_repetition)
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

/*
** prepare_hist_t_line:
**
** Prepare the t_line element in which we will add our
** command line.
*/

static int     prepare_hist_t_line(t_line **line_to_create)
{
    if (create_t_line(line_to_create, 0) == MALLOC_ERROR)
        return (MALLOC_ERROR);
    if (insert_string(&(*line_to_create)->chars, "> ", TRUE) == MALLOC_ERROR)
        return (free_t_line(line_to_create, MALLOC_ERROR));
    return (MALLOC_SUCCESS);
}

/*
** convert_char:
**
** Convert each char of a string into a t_char chained list,
** only to the end of the string or to a newline.
** Allocate a new line if it's needed.
*/

static int     convert_char(char *history_line, t_line **line_to_fill)
{
    if (!*line_to_fill)
    {
        if (prepare_hist_t_line(line_to_fill) == MALLOC_ERROR)
            return (MALLOC_ERROR);
    }
    while (*history_line && *history_line != '\n')
    {
        if (!push_end_char(&(*line_to_fill)->chars, *history_line++, FALSE))
            return (MALLOC_ERROR);
    }
    return (MALLOC_SUCCESS);
}

/*
** add_new_history:
**
** Add each line of the new history into the t_line chained list.
** Append in a first time the first line, and loop over each newline
** to create different t_list node.
*/

static int     add_new_history(t_line *shell_repr, t_cursor *cursor, t_hist *history)
{
    t_line *cursor_line;
    char    *hist_line;
    t_line  *followed_save;
    int     status;

    cursor_line = get_cursor_line(shell_repr, cursor);
    followed_save = cursor_line->next;
    hist_line = history ? history->line : "\0";
    if (convert_char(hist_line, &cursor_line) == MALLOC_ERROR)
        return (MALLOC_ERROR);
    if (!history)
        return (MALLOC_SUCCESS);
    cursor_line->next = NULL;
    status = MALLOC_SUCCESS;
    while ((hist_line = ft_strchr(hist_line, '\n')) && status)
    {
        hist_line++;
        status = convert_char(hist_line, &cursor_line->next);
        if (status == MALLOC_SUCCESS)
            cursor_line = cursor_line->next;
    }
    cursor_line->next = followed_save;
    update_line_lst(shell_repr);
    return (status);
}

int		history_manager(char *key, t_line *shell_repr, t_cursor *cursor)
{
	static int	    is_repetition = FALSE;
	static t_hist	*history = NULL;
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
