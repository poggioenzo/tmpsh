#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"
#include "run_ast.h"
#include "termios_setter.h"
#include "ast.h"

static int		run_file(char *filename)
{
	char			*content;
	t_tagstokens	*tagstoks;

	if(!(content = readfile(filename)))
		return (ft_dprintf(2, "tmpsh: Error with %s\n", filename));
	tagstoks = NULL;
	input_init_tagstokens(&tagstoks, content);
	if (tagstoks->incomplete)
		return (ft_dprintf(2, "tmpsh: Error with %s\n", filename));
	if (tagstoks->valid && !tagstoks->incomplete)
	{
		executor(init_ast(tagstoks));
		manage_termios(remove_config);
	}
	else
		ft_dprintf(2, "tmpsh: sytax error near %s\n", tagstoks->token_error);
	return (0);
}

void	run_shell_files(char **files)
{
	g_jobs->allow_background = false;
	while (*files)
		run_file(*files++);
}
