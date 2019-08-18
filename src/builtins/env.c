
#include "tmpsh.h"
#include "libft.h"
#include "environ_utils.h"
#include "path_check.h"

static void		empty_environ(void)
{
	int		index;

	index = 0;
	while (g_environ[index])
		ft_strdel(g_environ + index++);
}

static void		show_env(void)
{
	int		index;

	index = 0;
	while (g_environ[index])
		ft_printf("%s\n", g_environ[index++]);
}

static char		*find_execfile(char **args)
{
	int		index;

	index = 0;
	while (args[index] && ft_strchr(args[index], '='))
		index++;
	return (args[index] ? get_exec_file(args[index]) : NULL);
}

static void		prepare_env(char **args, char **executable_file)
{
	int		empty;

	empty = ft_array_in(args, "-i") ? TRUE : FALSE;
	if (empty)
		ft_array_remove(args, "-i", TRUE);
	*executable_file = find_execfile(args);
	if (empty)
		empty_environ();
}

int		built_env(char **args, char **environ)
{
	int		index;
	pid_t	pid;
	char	*executable;

	UNUSED(environ);
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
		perror("execve"); //Not good.
	}
	else
		show_env();
	return (0);
}
