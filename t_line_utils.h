#ifndef T_LINE_UTILS_H
# define T_LINE_UTILS_H

# include "libft.h"
# include "t_char_utils.h"
# include "tmpsh.h"

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

#endif
