/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:37:33 by simrossi    ###    #+. /#+    ###.fr     */
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
#include "file_runner.h"
#include <fcntl.h>

enum e_tagstoks_state		script_execute(char *script)
{
	enum e_tagstoks_state		state;
	t_tagstokens				*tagstoks;

	g_jobs->allow_background = false;
	tagstoks = NULL;
	routine_tagstokens(&tagstoks, script);
	if (tagstoks->incomplete)
	{
		ft_dprintf(2, NAME_SH" incomplete script.\n");
		state = incomplete_script;
	}
	else if (tagstoks->valid && !tagstoks->incomplete)
	{
		executor(init_ast(tagstoks));
		manage_termios(remove_config);
		state = complete_script;
	}
	else
	{
		ft_dprintf(2, NAME_SH" syntax error near %s\n", tagstoks->token_error);
		state = invalid_script;
	}
	free_tagstokens(&tagstoks, 0);
	return (state);
}

/*
** run_file:
**
** Create and run an AST from a file.
** Check if the given AST is correct before launching it.
*/

enum e_tagstoks_state		run_file(char *filename)
{
	char					*content;
	int						file_fd;
	enum e_tagstoks_state	state;

	if (!check_rights(filename, F | R | VERBOSE, false, true))
		return (1);
	file_fd = open(filename, O_RDONLY);
	if (!(content = fd_readfile(file_fd)))
		return (ft_dprintf(2, NAME_SH" Error with %s\n", filename));
	state = script_execute(content);
	ft_strdel(&content);
	return (state);
}

/*
** run_shell_files:
**
** Go through each file of argv and execute them one
** by one.
*/

int							run_shell_files(char **files)
{
	int		state;

	state = 0;
	while (*files)
	{
		if (run_file(*files++) != complete_script)
			g_last_status = 1;
	}
	return (g_last_status);
}
