#include "tmpsh.h"
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "grammar_init.h"

#include "libft.h"
#include "builtins.h"

int		g_last_status;

int		main(int argc, char **argv, char **environ)
{
	char	*grammar_abs;
	char	*grammar_file = "/pyshell/grammar/grammar.txt";

	UNUSED(argc);
	UNUSED(argv);
	UNUSED(environ);
	setup_freefct();
	grammar_abs = getcwd(NULL, 0);
	grammar_abs = ft_fstrjoin(&grammar_abs, &grammar_file, true, false);
	grammar_init(grammar_abs);
	FREE(grammar_abs);
	setup_builtins();
	//setup_variables_elements(environ);

	/*
	fd_debug = open("/dev/ttys003",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		return (prompt_loop());
	return (status);
	*/
}
