#include "file_management.h"
#include "get_next_command.h"
#include "t_char_allocation.h"
#include "t_hist_allocation.h"
#include "replace_home.h"
#include "libft.h"
#include <fcntl.h>

/*
** rewrite_history:
**
** Write the current content of the t_hist chained list
** in his appropriate file. Format each line properly.
*/

int			rewrite_history(t_hist *history)
{
	unsigned int	index;
	int		hist_fd;
	char	*history_filename;

	history_filename = replace_home(HISTORY_FILE);
	hist_fd = open(history_filename, O_CREAT | O_WRONLY, 0600);
	ft_strdel(&history_filename);
	if (hist_fd == -1)
		return (FAILURE);
	index = 0;
	while (history)
	{
		ft_dprintf(hist_fd, "#%u: %s\n", index++, history->line);
		history = history->next;
	}
	close(hist_fd);
	return (SUCCESS); // DEPEND OF OPEN
}

/*
** store_history:
**
** Store in a t_hist chained list the content of the history file.
*/

void		load_history(t_hist **history)
{
	char	*history_file;
	char	*command_to_add;

	*history = NULL;
	history_file = replace_home(HISTORY_FILE);
	if (access(history_file, R_OK) == -1)
		return ;
	while ((command_to_add = get_next_command(history_file)))
		push_t_hist(history, command_to_add, FALSE);
	ft_strdel(&history_file);
}
