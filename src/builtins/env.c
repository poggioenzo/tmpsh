/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 10:48:19 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"
#include "variables.h"
#include "exec_file.h"
#include <sys/wait.h>

/*
** empty_environ:
**
** Remove manually the g_environ variable.
** (Not really good)
*/

static void			empty_environ(void)
{
	int		index;

	index = 0;
	while (g_environ[index])
		ft_strdel(g_environ + index++);
}

/*
** show_env:
**
** Print the entire environnement on stdout.
*/

static void			show_env(void)
{
	int		index;

	index = 0;
	while (g_environ[index])
		ft_printf("%s\n", g_environ[index++]);
}

/*
** find_execfile:
**
** Parse the program args to find the command name,
** skipping all assignation.
**
** return : - Executable file on success.
**			- NULL if env have no command.
*/

static char			*find_execfile(char **args)
{
	int		index;

	index = 0;
	while (args[index] && ft_strchr(args[index], '='))
		index++;
	return (args[index] ? get_execname(args[index], true) : NULL);
}

/*
** prepare_env:
**
** Check if the -i options is activate, if it's the case,
** empty the current environnement.
** Search the executable file before removing the current
** environnement.
*/

static void			prepare_env(char **args, char **executable_file)
{
	int		empty;

	empty = ft_strequ(*args, "-i");
	if (empty)
		ft_array_remove(args, "-i", TRUE);
	*executable_file = find_execfile(args);
	if (empty)
		empty_environ();
}

/*
** built_env:
**
** env - set the environment for command invocation
**
** Synopsis : env [-i] [name=value]... [utility [argument...]]
**
** Launch the command utility with the given environnement.
**
** Options:
** -i : Invoke utility with exactly the environment specified by
**		the arguments; the inherited environment shall be
**		ignored completely
*/

int					built_env(char **args, NOT_USE(char **environ))
{
	int		index;
	pid_t	pid;
	char	*executable;

	if ((pid = fork()) > 0)
	{
		waitpid(pid, NULL, 0);
		return (0);
	}
	prepare_env(args, &executable);
	index = 0;
	while (args[index] && ft_strchr(args[index], '='))
	{
		ft_strreplace(args[index], '=', '\0');
		ft_setenv(args[index], args[index] + ft_strlen(args[index]) + 1);
		index++;
	}
	if (args[index])
	{
		execve(executable, args + index, g_environ);
		exit(1);
	}
	else
		show_env();
	exit(0);
}
