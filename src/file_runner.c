#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"
#include "run_ast.h"
#include "termios_setter.h"

static int		run_file(char *filename)
{
	char			*content;
	t_tagstokens	*tagstoks;

	if(!(content = readfile(filename)))
		return (ft_dprintf(2, "tmpsh: Error with %s\n", filename));
	tagstoks = NULL;
	ft_printf("content : |%s|\n", content);
	ft_printf("content : |%p|\n", content);
	input_init_tagstokens(&tagstoks, content);
	ft_printf("ptr: %p\n", tagstoks);
	if (tagstoks->incomplete)
		return (ft_dprintf(2, "tmpsh: Error with %s\n", filename));
	if (tagstoks->valid && !tagstoks->incomplete)
	{
		manage_termios(remove_term);
		executor(init_ast(tagstoks));
		manage_termios(restore_term);
	}
	else
		ft_dprintf(2, "tmpsh: sytax error near %s\n", tagstoks->token_error);
	return (0);
}

void	run_shell_files(char **files)
{
	while (*files)
		run_file(*files++);
}
