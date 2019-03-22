#ifndef T_CHAR_UTILS_H
# define T_CHAR_UTILS_H

# include "libft.h"
# include "tmpsh.h"

int			free_t_char_lst(t_char **char_lst, int status);
int			create_char(t_char	**char_node, char letter, int position, int lock);
int			push_end_char(t_char **char_node, char letter, int lock);
int			extend_char(t_char *old_chars, t_char *char_to_add);
int			insert_string(t_char **char_lst, char *string, int lock);
void		display_chars(t_char *char_lst, t_cursor *cursor, int line, \
							int *printed_cursor);
void		update_position(t_char *char_lst);
int			char_lst_len(t_char *char_lst);
int			char_lock_len(t_char *char_lst);
int			insert_char(t_line *shell_repr, char letter, t_cursor *cursor);
t_char		*get_unlocked_char(t_char *char_lst);
void		display_chars(t_char *char_lst, t_cursor *cursor, int line, \
		int *printed_cursor);
void		free_t_char(t_char **char_node);
t_char		*get_unlocked_char(t_char *char_lst);
#endif
