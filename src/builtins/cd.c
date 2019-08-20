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

static int		check_rights(char *filename)
{
	if (access(filename, F_OK) == -1)
		return (0);
	if (access(filename, X_OK) == -1)
		return (0);
}

static char		*parse_cdpath(char *pathname)
{
	char	*cdpath;
	char	**split_folders;
	int		index;
	char	*new_dir;

	cdpath = ft_getenv("CDPATH");
	if (!cdpath)
		return (pathname);
	split_folders = ft_strsplit(cdpath, ":");
	index = 0;
	while (split_folders[index])
	{
		new_dir = ft_filejoin
	}
}

int		built_cd(char **argv, char **environ)
{
	t_pylst		*options;
	int			argc;
	char		*new_dir;

	options = argparser(argv);
	argc = ft_arraylen(argv);
	if (argc == 0 && !(new_dir = ft_getenv("HOME")))
		return (free_pylst(&options, 0));
	if (argc >= 2)
	{
		ft_printf("cd: too much arguments\n");
		return (free_pylst(&options, 1));
	}
	if (argv[0][0] == '/')
		new_dir = argv[0];
	else if (ft_start_with(argv[0], ".") || ft_start_with(argv[0], ".."))
		new_dir = parse_cdpath(argv[0]);
	else
		new_dir = argv[0];
}
