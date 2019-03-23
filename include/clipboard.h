#ifndef CLIPBOARD_H
# define CLIPBOARD_H

# include "tmpsh.h"

int		clipoard_manager(char *key, t_line *shell_repr, t_cursor *cursor);
int		is_clipoard_key(char *key);
void	clipboard_store(int action, char **clipped_str);
#endif
