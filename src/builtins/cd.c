/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 13:44:10 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "cd_canon.h"
#include "cd_finder.h"
#include "argparser.h"
#include "variables.h"

char		*g_shell_dir;

/*
** check_option:
**
** Verify if the user is giving valid options for cd.
**
** return : - true if options are valid.
**			- false if an option is invalid.
*/

static int	check_option(t_pylst *options)
{
	char		*select_option;

	if (!options)
		return (true);
	while (iter_pylst(options, (void **)&select_option))
	{
		if (!in(select_option, "L", "P", NULL))
		{
			ft_dprintf(2, "cd: invalid option %s\n", select_option);
			return (free_pylst(&options, false));
		}
	}
	return (true);
}

/*
** change_directory:
**
** @directory: Expected new directory.
** @is_p: true if P options is activated, false otherwise.
**
** Try to change the working directory to @directory.
** On success, setup PWD and OLDPWD environnement variables,
** according to the options.
**
** return : - 0 on success.
**			- 1 if the working directory don't change.
*/

static int	change_directory(char *directory, int is_p)
{
	char		*cwd;

	if (!allowed_access(directory, true))
		return (1);
	if (chdir(directory) == 0)
	{
		ft_setenv("OLDPWD", g_shell_dir);
		ft_strdel(&g_shell_dir);
		if (is_p)
		{
			cwd = getcwd(NULL, 0);
			ft_strdel(&directory);
			directory = ft_strdup(cwd);
			free(cwd);
		}
		ft_strdel(&g_shell_dir);
		g_shell_dir = directory;
		ft_setenv("PWD", g_shell_dir);
		return (0);
	}
	else
		ft_dprintf(2, NAME_SH" : %s not a directory\n", directory);
	ft_strdel(&directory);
	return (1);
}

/*
** built_cd:
**
** Builtin for the cd command. POSIX compliant.
** Available options : -P | -L
**
** Allow directory research with CDPATH variable.
** Manage symlink directories by using canonical form
** of the directory when using chdir.
*/

int			built_cd(char **argv, NOT_USE(char **environ))
{
	t_pylst		*options;
	char		*new_dir;
	int			status;
	int			is_p;

	options = argparser(argv);
	if (ft_arraylen(argv) >= 2)
	{
		ft_printf("cd: too much arguments\n");
		return (free_pylst(&options, 1));
	}
	if (check_option(options) == false)
		return (1);
	is_p = options && *(char *)vindex_pylst(options, -1) == 'P';
	if (!(new_dir = find_newdir(argv[0], is_p)))
		return (1);
	status = change_directory(new_dir, is_p);
	free_pylst(&options, 0);
	return (status);
}
