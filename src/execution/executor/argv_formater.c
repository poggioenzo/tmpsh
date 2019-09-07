/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
	t_pylst		*command;
	char		*tag;
	char		*token;

	command = NULL;
	while (iter_tagstokens(branch->tagstokens, &token, &tag))
	{
		if (ft_strequ(tag, "STMT"))
			push_pylst(&command, token, ft_strlen(token) + 1, _chare);
	}
	return (convert_command(command));
}
