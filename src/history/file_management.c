#include "file_management.h"
#include "get_next_command.h"
#include "t_char_allocation.h"
#include "t_hist_allocation.h"
#include "replace_home.h"
#include "libft.h"
#include <fcntl.h>


/*
** write_line:
**
** Format a single command of the history and write it to the given
** file descriptor.
** Format like "#123: my_command" followed by a newline.
*/

static int		write_line(unsigned int index, int hist_fd, char *command)
{
	char	*str_index;

	if (!(str_index = ft_utoa(index)))
		return (MALLOC_ERROR);
	write(hist_fd, "#", 1);
	write(hist_fd, str_index, ft_strlen(str_index));
	write(hist_fd, ": ", 2);
	write(hist_fd, command, ft_strlen(command));
	write(hist_fd, "\n", 1);
	ft_strdel(&str_index);
	return (SUCCESS);
}

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

	if (!(history_filename = replace_home(HISTORY_FILE)))
		return (MALLOC_ERROR);
	if ((hist_fd = open(history_filename, O_CREAT | O_WRONLY, 0600)) == -1)
		return (ft_strdel_out(&history_filename, FAILURE));
	ft_strdel(&history_filename);
	index = 0;
	while (history)
	{
		if (write_line(index++, hist_fd, history->line) == MALLOC_ERROR)
		{
			close(hist_fd);
			return (MALLOC_ERROR);
		}
		history = history->next;
	}
	close(hist_fd);
	return (SUCCESS);
}

/*
** read_history_file:
**
** Store each command in the history file and add it into
** our t_hist chained list.
*/

static int		read_history_file(char *history_filename, t_hist **history)
{
	char	*command_to_add;

	if (!(command_to_add = ft_strnew(0)))
		return (MALLOC_ERROR);
	while (get_next_command(history_filename, &command_to_add) == SUCCESS)
	{
		if (command_to_add)
		{
			if (!extend_history(&history, &command_to_add))
				return (MALLOC_ERROR);
		}
		else
			return (SUCCESS);
	}
	return (FAILURE);
}

/*
** store_history:
**
** Store in a t_hist chained list the content of the history file.
*/

int		store_history(t_hist **history)
{
	char	*history_file;
	int		status;

	*history = NULL;
	if (!(history_file = replace_home(HISTORY_FILE)))
		return (FAILURE);
	status = read_history_file(history_file, history);
	ft_strdel(&history_file);
	return (status == SUCCESS ? status : free_history(history, status));
}
