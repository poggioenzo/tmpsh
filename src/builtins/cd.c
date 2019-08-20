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

static int		allowed_access(char *filename)
{
	if (access(filename, F_OK) == -1)
		return (0);
	if (access(filename, X_OK) == -1)
		return (0);
	return (1);
}

static char		*parse_cdpath(char *pathname)
{
	char	*cdpath;
	char	**split_folders;
	int		index;
	char	*new_dir;
	char	*tmp;

	if (!(cdpath = ft_getenv("CDPATH")))
		return (pathname);
	split_folders = ft_strsplit(cdpath, ":");
	index = 0;
	new_dir = NULL;
	while (split_folders[index])
	{
		new_dir = ft_filejoin(split_folders[index], pathname, false, false);
		if (allowed_access(new_dir))
			break ;
		ft_strdel(&new_dir);
		tmp = "./";
		new_dir = ft_filejoin(&tmp, &new_dir, false, true);
		if (allowed_access(new_dir))
			break ;
		ft_strdel(&new_dir);
		index++;
	}
	free_str_array(&split_folders);
	return (new_dir ? new_dir : ft_strdup(pathname));
}

int		check_option(t_pylst *options)
{
	t_pylst		*parse_opt;
	char		*select_option;

	if (!options)
		return (true);
	while (iter_pylst(options, (void **)&select_option))
	{
		if (!(ft_strequ(select_option, "L")  || ft_strequ(select_option, "P")))
		{
			ft_dprintf(2, "cd: invalid option %s\n", select_option);
			return (free_pylst(&options, false));
		}
	}
	return (true);
}

void	change_directory(char *directory, t_pylst *options)
{
	if (!allowed_access(directory))
		return ;

}

int		built_cd(char **argv, char **environ)
{
	t_pylst		*options;
	int			argc;
	char		*new_dir;

	options = argparser(argv);
	argc = ft_arraylen(argv);
	if (argc >= 2)
	{
		ft_printf("cd: too much arguments\n");
		return (free_pylst(&options, 1));
	}
	if (check_option(options) == false)
		return (1);
	if (argc == 0 && !(new_dir = ft_getenv("HOME")))
		return (free_pylst(&options, 0));
	new_dir = new_dir ? ft_strdup(new_dir) : NULL;
	else if (argv[0][0] == '/')
		new_dir = ft_strdup(argv[0]);
	else if (ft_start_with(argv[0], ".") || ft_start_with(argv[0], ".."))
		new_dir = ft_strdup(argv[0]);
	else
		new_dir = parse_cdpath(argv[0]);
	change_directory(new_dir);
	free_pylst(&options);
}
