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

int		main(int argc, char **argv, char **environ)
{
	setup_globals(environ);
	if (argc == 1)
	{
		source_rc();
		prompt_loop();
	}
	else
		run_shell_files(argv + 1);
	remove_globals();
	return (0);
}
