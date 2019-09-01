#include "tmpsh.h"
#include "environ_utils.h"
#include "variable_management.h"
#include "prompt_loop.h"
#include <fcntl.h>
#include "variables.h"
#include "job_control.h"
#include "foreground.h"

#include "setup_shell_freefct.h"
#include "tagstokens.h"
#include "grammar_init.h"
#include "ast.h"

#include "libft.h"
#include "builtins.h"

int		g_last_status;
t_pylst 	*g_heredocs;
t_pylst 	*g_passed_alias;

void	setup_globals(char **environ)
{
	char	*grammar_file;
	char	*cwd;

	setup_freefct();
	g_heredocs = NULL;
	g_passed_alias = NULL;
	grammar_file = "/pyshell/grammar/grammar.txt";
	cwd = getcwd(NULL, 0);
	g_shell_dir = ft_strdup(cwd);
	free(cwd);
	grammar_file = ft_strjoin(g_shell_dir, grammar_file);
	grammar_init(grammar_file);
	setup_builtins();
	setup_variables_elements(environ);
	ht_new_table(&g_alias, 47, 65);
	ht_new_table(&g_hash, 47, 50);
	init_backgroundjobs();
	init_tcsettings();
}

void	remove_globals(void)
{
	ft_strdel(&g_shell_dir);
	free_hash_table(&g_variables, 0);
	free_hash_table(&g_builtins, 0);
	free_str_array(&g_environ, 0);
	free_hash_table(&g_alias, 0);
	free_hash_table(&g_hash, 0);


	//Depend if we allow leaving the programm with or without background jobs.
	//free_pylst(&g_jobs->list_jobs);
	ft_memdel((void **)&g_jobs);
	free_grammar();

}

//int		main(NOT_USE(int argc), NOT_USE(char **argv), NOT_USE(char **environ))
int		main(int argc, char **argv, NOT_USE(char **environ))
{
	int status;
	setup_globals(environ);
	// setup_variables_elements(environ);
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
	setup_shell_freefct();
	cwd = getcwd(NULL, 0);
	grammar_abs = ft_strjoin(cwd, grammar_file);
	free(cwd);
	grammar_init(grammar_abs);
	FREE(grammar_abs);
	input_init_tagstokens(&tgtk, argv[1]);
	// print_tagstokens(tgtk);
	ast = init_ast(tgtk);
	ft_printf("%s\n", str_ast(ast));
	free_ast(&ast);
	free_tagstokens(&tgtk, TRUE);
	return ((status=0));

	// fd_debug = open("/dev/ttys003",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	// if (argc == 1)
	// 	prompt_loop();
	// remove_globals();
	// return ((status=0));


}
