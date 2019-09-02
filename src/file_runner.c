#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"
#include "run_ast.h"
#include "termios_setter.h"
#include "ast.h"
#include "exec_file.h"
#include <fcntl.h>

/*
** check_rights:
**
** When the shell research exepected executable, check
** if it's possible to run the given file.
** Check permission + file existence.
*/

static t_bool	check_rights(char *cmd)
{
	char	*err_msg;

	err_msg = NULL;
	if (access(cmd, F_OK) == -1)
		err_msg = NAME_SH" No such file or directory : %s\n";
	else if (is_directory(cmd))
		err_msg = NAME_SH" %s: is a directory\n";
	else if (access(cmd, R_OK) == -1 || access(cmd, R_OK) == -1)
		err_msg = NAME_SH" permission denied: %s\n";
	if (err_msg)
	{
		ft_dprintf(STDERR_FILENO, err_msg, cmd);
		return (false);
	}
	return (true);
}

/*
** run_file:
**
** Create and run an AST from a file.
** Check if the given AST is correct before launching it.
*/

int		run_file(char *filename)
{
	char			*content;
	t_tagstokens	*tagstoks;
	int				file_fd;

	if (!check_rights(filename))
		return (1);
	file_fd = open(filename, O_RDONLY);
	if (!(content = fd_readfile(file_fd)))
		return (ft_dprintf(2, NAME_SH" Error with %s\n", filename));
	tagstoks = NULL;
	// free_pylst(&g_passed_alias, 0);
	input_init_tagstokens(&tagstoks, content);
	if (tagstoks->incomplete)
		return (ft_dprintf(2, NAME_SH" Error with %s\n", filename));
	if (tagstoks->valid && !tagstoks->incomplete)
	{
		executor(init_ast(tagstoks));
		manage_termios(remove_config);
	}
	else
		ft_dprintf(2, NAME_SH" sytax error near %s\n", tagstoks->token_error);
	return (0);
}

/*
** run_shell_files:
**
** Go through each file of argv and execute them one
** by one.
*/

void			run_shell_files(char **files)
{
	g_jobs->allow_background = false;
	while (*files)
		run_file(*files++);
}
