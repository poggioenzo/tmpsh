#ifndef T_CHAR_UTILS_H
# define T_CHAR_UTILS_H

# include "libft.h"
# include "tmpsh.h"
# include "t_cursor_utils.h"

typedef struct s_char	t_char;

struct	s_char
{
	char		letter;
	short		lock:1;
	short		position;
	t_char		*next;
	t_char		*prev;

};

int			free_t_char_lst(t_char **char_lst, int status);
int			push_end_char(t_char **char_node, char letter, int lock);
int			insert_string(t_char **char_lst, char *string, int lock);
void		display_chars(t_char *char_lst, t_cursor *cursor, int line);

#endif
