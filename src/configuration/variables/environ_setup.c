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
#include "variables.h"

char		**g_environ;

/*
** get_path_default:
**
** Retrieve default exec folder of /etc/paths. Format
** them in the PATH format to be set further.
*/

static char		*get_path_default(void)
{
	char	*paths_content;

	paths_content = readfile("/etc/paths");
	ft_strreplace(paths_content, '\n', ':');
	paths_content[ft_strlen(paths_content) - 1] = '\0';
	return (paths_content);
}

/*
** duplicate_environ:
**
** Simple copy of the char **environ variable at the shell setup.
** If no PATH variable is avaible, setup the default PATH value
** stored in /etc/paths
*/

void			duplicate_environ(char **environ)
{
	char	*bins_files;

	g_environ = ft_duparray(environ);
	if (ft_getenv("PATH") == NULL)
	{
		bins_files = get_path_default();
		ft_setenv("PATH", bins_files);
		ft_strdel(&bins_files);
	}
}
