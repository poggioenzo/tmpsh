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

int     add_new_history(t_line *shell_repr, t_cursor *cursor, t_hist *history)
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
