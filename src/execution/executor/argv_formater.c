#include "tmpsh.h"
#include "libft.h"
#include "tagstokens.h"

/*
** convert_command:
**
** Convert a command in a pylst format into a char ** format, like argv.
*/

static char		**convert_command(t_pylst *command)
{
	char	**cmd_array;
	int		index;

	cmd_array = ft_memalloc(sizeof(char *) * (len_pylst(command) + 1));
	index = 0;
	while (command)
		cmd_array[index++] = pop_pylst(&command, 0);
	cmd_array[index] = NULL;
	return (cmd_array);
}

/*
** extract_cmd:
**
** Get only token used to run a command, format argv.
*/

char			**extract_cmd(t_acb *branch)
{
	size_t		index;
	t_pylst		*command;
	char		*tag;
	char		*token;

	index = 0;
	command = NULL;
	while (index < branch->tagstokens->length)
	{
		tag = vindex_pylst(branch->tagstokens->tags, index);
		if (ft_strequ(tag, "STMT"))
		{
			token = vindex_pylst(branch->tagstokens->tokens, index);
			push_pylst(&command, token, ft_strlen(token) + 1, _chare);
		}
		index++;
	}
	return (convert_command(command));
}
