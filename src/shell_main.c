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
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "tagstokens.h"
#include "ast.h"
#include "file_runner.h"

#include "globals_setup.h"

void	source_rc(void)
{
	char	*filename;
	char	*home;

	if ((home = ft_getenv("HOME")))
	{
		filename = RC_FILE;
		filename = ft_filejoin(&home, &filename, false, false);
	}
	else
		filename = ft_strdup(RC_FILE);
	g_jobs->allow_background = false;
	run_file(filename);
	ft_strdel(&filename);
	g_jobs->allow_background = true;
}

int		run_stdin_file(void)
{
	char	*fd_content;
	int		state;

	if (!(fd_content = fd_readfile(0)))
		return (1);
	state = script_execute(fd_content);
	return (state == complete_script ? 0 : 1);
}

int		main(int argc, char **argv, char **environ)
{
	int		status;

	setup_globals(environ);
	status = 0;
	if (argc == 1)
	{
		if (!isatty(STDIN_FILENO))
			status = run_stdin_file();
		else if (isatty(STDOUT_FILENO))
		{
			source_rc();
			prompt_loop();
			status = g_last_status;
		}
		else
		{
			ft_dprintf(2, NAME_SH" no controlling terminal.\n");
			status = 1;
		}
	}
	else
		status = run_shell_files(argv + 1);
	remove_globals();
	return (status);
}
