#include "tmpsh.h"
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "tagstokens.h"
#include "grammar_init.h"

#include "libft.h"
#include "builtins.h"

int		main(int argc, char **argv)//char **environ)
{
	char	*grammar_abs;
	char	*grammar_file = "/pyshell/grammar/grammar.txt";
	char	*cwd;
	t_tagstokens *tgtk;

	if (argc != 2)
	{
		ft_printf("Usage:"PURPLE" ./tmpsh 'command'\n"WHITE);
		return (64);
	}
	tgtk = NULL;
	setup_freefct();
	cwd = getcwd(NULL, 0);
	grammar_abs = ft_strjoin(cwd, grammar_file);
	free(cwd);
	grammar_init(grammar_abs);
	FREE(grammar_abs);
	input_init_tagstokens(&tgtk, argv[1]);
	print_tagstokens(tgtk);
	free_tagstokens(&tgtk, TRUE);
	return (0);
}
