#include "environ_utils.h"
#include "libft.h"

static char		*get_oldpwd(void)
{
	char	*oldpwd;

	if (!(oldpwd = ft_getenv("OLDPWD")))
		ft_dprintf(2, "cd : OLDPWD not set.\n");
	return (oldpwd);
}

int			built_cd(char **args, char **environ)
{
	char	*direction;
	char	*oldpwd;

	UNUSED(environ);
	if (ft_arraylen(args) >= 2 && ft_dprintf(2, "cd : too many arguments.\n"))
		return (1);
	if (*args)
		direction = *args;
	else
		if (!(direction = ft_getenv("HOME")))
			return (0);
	if (ft_strequ(direction, "-"))
		if (!(direction = get_oldpwd()))
			return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(direction) == -1)
	{
		ft_dprintf(2, "cd : Probably a right error or no such directory : %s\n",
				direction);
		return (1);
	}
	ft_setenv("OLDPWD", oldpwd);
	ft_strdel(&oldpwd);
	return (0);
}
