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

#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"
#include "run_ast.h"
#include "termios_setter.h"
#include "ast.h"
#include "exec_file.h"
#include "file_rights.h"
#include <fcntl.h>

/*
** run_file:
**
** Create and run an AST from a file.
** Check if the given AST is correct before launching it.
*/

int				run_file(char *filename)
{
	char			*content;
	t_tagstokens	*tagstoks;
	int				file_fd;

	if (!check_rights(filename, F | R, false, true))
		return (1);
	file_fd = open(filename, O_RDONLY);
	if (!(content = fd_readfile(file_fd)))
		return (ft_dprintf(2, NAME_SH" Error with %s\n", filename));
	tagstoks = NULL;
	routine_tagstokens(&tagstoks, content);
	ft_strdel(&content);
	if (tagstoks->incomplete)
		ft_dprintf(2, NAME_SH" Error with %s\n", filename);
	else if (tagstoks->valid && !tagstoks->incomplete)
	{
		executor(init_ast(tagstoks));
		manage_termios(remove_config);
	}
	else
		ft_dprintf(2, NAME_SH" syntax error near %s\n", tagstoks->token_error);
	free_tagstokens(&tagstoks, 0);
	return (0);
}

/*
** run_shell_files:
**
** Go through each file of argv and execute them one
** by one.
*/

void			run_shell_files(char **files)
{
	g_jobs->allow_background = false;
	while (*files)
		run_file(*files++);
}
