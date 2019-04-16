#include "environ_utils.h"
#include "tmpsh.h"
#include "libft.h"

static char		*get_path_default(void)
{
	char	*paths_content;

	if (!(paths_content = readfile("/etc/paths", 0, 0)))
		exit(-1);
	ft_strreplace(paths_content, '\n', ':');
	paths_content[ft_strlen(paths_content) - 1] = '\0';
	return (paths_content);

}

/*
** duplicate_environ:
**
** Simple copy of the char **environ variable.
*/

void	duplicate_environ(char **environ)
{
	if (!(g_environ = ft_duparray(environ)))
		exit(-1);
	if (ft_getenv("PATH") == NULL)
	{
		// Store path default with get_path_default()
	}
}

/*
** ft_getenv:
**
** Behave like getenv but for the local environnement.
*/

char	*ft_getenv(char *variable)
{
	int		index;

	index = 0;
	while (g_environ[index])
	{
		if (ft_start_with(g_environ[index], variable))
			return (g_environ[index] + ft_strlen(variable) + 1);
		index++;
	}
	return (NULL);
}
