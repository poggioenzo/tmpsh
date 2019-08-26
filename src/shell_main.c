#include "tmpsh.h"
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>

#include "tagstokens.h"
#include "grammar_init.h"
#include "ast.h"

#include "libft.h"
#include "builtins.h"

int		main(int argc, char **argv)//char **environ)
{
	DF;
	char	*grammar_abs;
	char	*grammar_file = "/pyshell/grammar/grammar.txt";
	char	*cwd;
	t_tagstokens *tgtk;
	t_ast *ast;

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
	// print_tagstokens(tgtk);
	ast = init_ast(tgtk);
	// ft_printf("%s\n", "LOL");
	ft_printf("%s\n", str_ast(ast));
	// ft_printf("%s\n", "LOL");
	free_tagstokens(&tgtk, TRUE);
	DFE;
	return (0);
}

/*
** ft_printf("%d\n", find_prev_ind_token(tgtk, 3));
** ft_printf("%s\n", find_prev_token(tgtk, 3, FALSE));
** ft_printf("%s\n", find_prev_token(tgtk, 3, TRUE));
** ft_printf("%d\n", find_next_ind_token(tgtk, 3));
** ft_printf("%s\n", find_next_token(tgtk, 3, FALSE));
** ft_printf("%s\n", find_next_token(tgtk, 3, TRUE));
*/
