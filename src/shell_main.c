#include "tmpsh.h"
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "grammar.h"

#include "libft.h"
#include "builtins.h"

int		main(int argc, char **argv, char **environ)
{
	int		status = 0;
	char	*grammar_abs;
	char	*grammar_file = "/pyshell/grammar/grammar.txt";

	grammar_abs = getcwd(NULL, 0);
	grammar_abs = ft_fstrjoin(&grammar_abs, &grammar_file, true, false);
	ft_printf("%s\n", grammar_abs);
	grammar_init(grammar_abs);
	FREE(grammar_abs);
	//setup_variables_elements(environ);

	/*
	fd_debug = open("/dev/ttys003",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	return (status);
	*/
}
