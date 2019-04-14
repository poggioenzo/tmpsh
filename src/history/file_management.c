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

static void		write_line(unsigned int index, int hist_fd, char *command)
{
	char	*str_index;

	if (!(str_index = ft_utoa(index)))
		exit(-1);
	write(hist_fd, "#", 1);
	write(hist_fd, str_index, ft_strlen(str_index));
	write(hist_fd, ": ", 2);
	write(hist_fd, command, ft_strlen(command));
	write(hist_fd, "\n", 1);
	ft_strdel(&str_index);
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

	history_filename = replace_home(HISTORY_FILE);
	if ((hist_fd = open(history_filename, O_CREAT | O_WRONLY, 0600)) == -1) // CHECK IF AN ERROR occur
		return (ft_strdel_out(&history_filename, FAILURE));
	ft_strdel(&history_filename);
	index = 0;
	while (history)
	{
		write_line(index++, hist_fd, history->line);
		history = history->next;
	}
	close(hist_fd);
	return (SUCCESS); // DEPEND OF OPEN
}

/*
** read_history_file:
**
** Store each command in the history file and add it into
** our t_hist chained list.
*/

static void		read_history_file(char *history_filename, t_hist **history)
{
	char	*command_to_add;

	while ((command_to_add = get_next_command(history_filename)))
		push_t_hist(history, command_to_add, FALSE);
}

/*
** store_history:
**
** Store in a t_hist chained list the content of the history file.
*/

void		load_history(t_hist **history)
{
	char	*history_file;

	*history = NULL;
	history_file = replace_home(HISTORY_FILE);
	read_history_file(history_file, history);
	ft_strdel(&history_file);
}
