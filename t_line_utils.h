#ifndef T_LINE_UTILS_H
# define T_LINE_UTILS_H

# include "libft.h"
# include "tmpsh.h"
# include "t_char_utils.h"

typedef struct s_line	t_line;

struct		s_line
{
	int			position;
	t_char		*chars;
	t_line		*prev;
	t_line		*next;
};

int		push_end_line(t_line **line_lst);
int		create_t_line(t_line **new_line, t_line *prev, int position);
int		free_t_line_lst(t_line **line_lst, int status);
int		is_cursor_last_pos(t_line *line_lst, t_cursor *cursor);
t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor);

#endif
