#include "get_next_command.h"
#include "libft.h"
#include <fcntl.h>

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

static char		*cut_next_command(char **command_list)
{
	char	*cursor_pos;
	int		len;
	char	*new_cmd;

	cursor_pos = *command_list;
	if (!*cursor_pos)
		return (NULL);
	cursor_pos++;
	while (ft_isdigit(*cursor_pos))
		cursor_pos++;
	cursor_pos += 2;
	len = command_len(cursor_pos);
	if (!(new_cmd = ft_strsub(cursor_pos, 0, len)))
		exit(-1);
	cursor_pos += len + 1;
	*command_list = cursor_pos;
	return (new_cmd);
}

/*
** get_next_command:
**
** Kind of get_next_line to extract command one by one.
** Will read the entire history file. Will use a specific pointer
** in one other side to move on in the file.
**
** return value:
** - SUCCESS if the next command have been found and is properly allocated,
** FAILURE if the allocation failed.
*/

char	*get_next_command(char *filename)
{
	static char		*history_content = NULL;
	static int		stored = FALSE;
	static char		*curr_pos;
	char			*command;

	if (!history_content && stored == FALSE)
	{
		if (!(history_content = readfile(filename, O_RDWR | O_CREAT, 0600))) // WHAT IF AN ERROR OCCUR ?
			exit(-1);
		curr_pos = history_content;
		stored = TRUE;
	}
	command = cut_next_command(&curr_pos);
	if (!command)
		ft_strdel(&history_content);
	return (command);
}
