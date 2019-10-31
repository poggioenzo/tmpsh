/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pwd.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 13:36:14 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:36:26 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "argparser.h"

static t_bool		parse_options(char **argv, int *p_flag, int *l_flag)
{
	t_pylst	*options;

	if (ft_arraylen(argv) >= 2)
	{
		ft_dprintf(2, "pwd: Too many arguments.\n");
		return (false);
	}
	*p_flag = false;
	*l_flag = false;
	options = argparser(argv);
	if (len_pylst(options) == 0)
		return (true);
	if (!in(options->value, "P", "L", NULL))
	{
		ft_dprintf(2, "pwd: bad option: -%s\n", options->value);
		return (free_pylst(&options, false));
	}
	if (ft_strequ(options->value, "P"))
		*p_flag = true;
	else
		*l_flag = false;
	return (free_pylst(&options, true));
}

int					built_pwd(char **argv, NOT_USE(char **environ))
{
	int		p_flag;
	int		l_flag;
	char	*cwd;
	char	*directory;

	if (parse_options(argv, &p_flag, &l_flag) == false)
		return (1);
	if (p_flag)
	{
		cwd = getcwd(NULL, 0);
		directory = ft_strdup(cwd);
		free(cwd);
	}
	else
		directory = ft_strdup(g_shell_dir);
	ft_printf("%s\n", directory);
	ft_strdel(&directory);
	return (0);
}
