#include "environ_utils.h"
#include "libft.h"

static char		*get_oldpwd(void)
{
	char	*oldpwd;

	if (!(oldpwd = ft_getenv("OLDPWD")))
	{
		ft_dprintf(2, "cd : OLDPWD not found, retry again.\n");
		return (NULL);
	}
	return (oldpwd);
}

void			built_cd(char **args)
{
	char	*direction;
	char	*oldpwd;

	if (*args)
	{
		direction = *args;
		if (ft_arraylen(args) >= 2 && ft_dprintf(2, "cd : Mayday Mayday.\n"))
			return ;
	}
	else
	{
		// Can get the home from the uid instead of environnement
		if (!(direction = ft_getenv("HOME")) && \
				ft_dprintf(2, "cd : HOME not set\n"))
			return ;
	}
	if (ft_strequ(direction, "-"))
		if (!(direction = get_oldpwd()))
			return ;
	oldpwd = getcwd(NULL, 0);
	if (chdir(direction) == -1)
		//Can use errno
		ft_dprintf(2, "cd : Probably a right error or no such directory : %s\n",
				direction);
	else
		ft_setenv("OLDPWD", oldpwd);
	ft_strdel(&oldpwd);
}
