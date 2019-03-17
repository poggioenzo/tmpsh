#include "history.h"
#include "replace_home.h"
#include "libft.h"
#include <fcntl.h>

/*
** create_t_hist:
**
** Allocate a single t_hist element, filling up his field.
*/

static int		create_t_hist(t_hist **hist_node, t_hist *prev, char *content)
{
	if (!(*hist_node = (t_hist *)malloc(sizeof(t_hist))))
		return (MALLOC_ERROR);
	(*hist_node)->line = content;
	(*hist_node)->next = NULL;
	(*hist_node)->prev = prev;
	return (MALLOC_SUCCESS);
}

/*
** pust_t_hist:
**
** Add to the t_hist chained list a new node.
** Push it at the end of our list.
*/

static int		push_t_hist(t_hist **history, char *content)
{
	t_hist	*curr_node;

	if (!*history)
		return (create_t_hist(history, NULL, content));
	curr_node = *history;
	while (curr_node->next)
		curr_node = curr_node->next;
	return (create_t_hist(&curr_node->next, curr_node, content));
}

/*
** is_new_command:
**
** Check if the given string seem to be a new command
** in the history.
**
** The history is having a format like : "#123: my_cmd"
*/

static int		is_new_command(char *line)
{
	int		index;

	index = 0;
	if (line[index++] != '#')
		return (FALSE);
	if (ft_isdigit(line[index++]) == FALSE)
		return (FALSE);
	while (ft_isdigit(line[index]))
		index++;
	if (line[index] == ':' && line[index + 1] == ' ')
		return (TRUE);
	return (FALSE);
}

/*
** free_history_node:
**
** Free a single element of t_hist.
*/

static void	free_history_node(t_hist **hist_node)
{
	free((*hist_node)->line);
	free(*hist_node);
	*hist_node = NULL;
}

/*
** free_history:
**
** Free an entire chained list of t_hist elements.
** Setting up his pointer to NULL, and returning status.
*/

static int		free_history(t_hist **history, int status)
{
	t_hist		*tmp_node;
	t_hist		*next_node;

	tmp_node = *history;
	while (tmp_node)
	{
		next_node = tmp_node->next;
		free_history_node(&tmp_node);
		tmp_node = next_node;
	}
	*history = NULL;
	return (status);
}

/*
** extend_history:
**
** Small utility to add a new command to our chained list and
** perform some check to see if we had an allocation error.
*/

static int		extend_history(t_hist ***history, char **new_command)
{
	if (push_t_hist(*history, *new_command) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (!(*new_command = ft_strnew(0)))
		return (MALLOC_ERROR);
	return (MALLOC_SUCCESS);
}

/*
** command_len:
**
** From our current commands list, get the len of the next command.
*/

static int		command_len(char *command)
{
	int		index;

	index = 0;
	while (command[index])
	{
		if (command[index] == '\n' && is_new_command(command + index + 1))
			break ;
		index++;
	}
	if (command[index] == '\0' && index > 0 && command[index - 1] == '\n')
		index--;
	return (index);
}

/*
** cut_next_command:
**
** Starting from the first line of a new command, extract
** the entire command. Incrementing our position in our list of command
** to start the next time at a command beginning.
*/

static int			cut_next_command(char **command_list, char **new_cmd)
{
	char	*cursor_pos;
	int		len;

	cursor_pos = *command_list;
	if (!*cursor_pos)
		return (SUCCESS);
	cursor_pos++;
	while (ft_isdigit(*cursor_pos))
		cursor_pos++;
	cursor_pos += 2;
	len = command_len(cursor_pos);
	if (len == 0)
		return (SUCCESS);
	*new_cmd = ft_strsub(cursor_pos, 0, len);
	cursor_pos += len + 1;
	*command_list = cursor_pos;
	return (*new_cmd ? SUCCESS : FAILURE);
}

/*
** get_next_command:
**
** Kind of get_next_line to extract command one by one.
** Will read the entire history file. Will use a specific pointer
** in one other side to move on in the file.
*/

static int		get_next_command(char *filename, char **command)
{
	static char		*history_content = NULL;
	static int		stored = FALSE;
	static char		*curr_pos;
	int				status;

	if (!history_content && stored == FALSE)
	{
		if (!(history_content = readfile(filename, O_RDWR | O_CREAT, 0600)))
			return (MALLOC_ERROR);
		curr_pos = history_content;
		stored = TRUE;
	}
	*command = NULL;
	status = cut_next_command(&curr_pos, command);
	if (status == SUCCESS && command == NULL)
		ft_strdel(&history_content);
	return (status);
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
