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


//To remove
#include "termios_setter.h"
int		g_last_status = 0;

void	setup_globals(char **environ)
{
	char	*grammar_file;
	char	*cwd;

	setup_freefct();
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

void	exit_termios(void)
{
	manage_termios(remove_term);
}

int		main(NOT_USE(int argc), NOT_USE(char **argv), NOT_USE(char **environ))
{
	int status;
	setup_globals(environ);
	// setup_variables_elements(environ);
	atexit(exit_termios);

	fd_debug = open("/dev/ttys003",  O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (argc == 1)
		prompt_loop();
	remove_globals();
	return ((status=0));
}
