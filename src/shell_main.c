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
	t_tagstokens *tgtk;

	if (argc != 2)
	{
		ft_printf("Usage:"PURPLE" ./tmpsh 'command'\n"WHITE);
		return (64);
	}
	tgtk = NULL;
	setup_freefct();
	grammar_abs = getcwd(NULL, 0);
	grammar_abs = ft_fstrjoin(&grammar_abs, &grammar_file, true, false);
	grammar_init(grammar_abs);
	FREE(grammar_abs);
	input_init_tagstokens(&tgtk, argv[1]);
	print_tagstokens(tgtk);
	// print_tagstokens(copy_tagstokens(tgtk, 1,3));
	// print_tagstokens(NULL);
	return (0);
}
