#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"
#include "run_ast.h"
#include "termios_setter.h"
#include "ast.h"

/*
** run_file:
**
** Create and run an AST from a file.
** Check if the given AST is correct before launching it.
*/

static int		run_file(char *filename)
{
	char			*content;
	t_tagstokens	*tagstoks;

	if(!(content = readfile(filename)))
		return (ft_dprintf(2, NAME_SH" Error with %s\n", filename));
	tagstoks = NULL;
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

void	run_shell_files(char **files)
{
	g_jobs->allow_background = false;
	while (*files)
		run_file(*files++);
}
