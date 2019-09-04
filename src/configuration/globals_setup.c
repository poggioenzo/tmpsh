#include "libft.h"
#include "tmpsh.h"
#include "file_rights.h"
#include "level_increment.h"
#include "builtins.h"
#include "termios_setter.h"
#include "grammar_init.h"
#include "variables.h"
#include "job_control.h"
#include "foreground.h"

int			g_last_status = 0;
pid_t		g_last_pid = 0;
t_pylst 	*g_heredocs;
t_pylst 	*g_passed_alias;
t_pylst 	*g_actual_alias;
int			g_aliasindepth = 0;
char		g_last_char[5];

void	setup_globals(char **environ)
{
	char	*grammar_file;
	char	*cwd;

	setup_freefct();
	g_heredocs = NULL;
	g_passed_alias = NULL;
	g_actual_alias = NULL;
	grammar_file = "/pyshell/grammar/grammar.txt";
	cwd = getcwd(NULL, 0);
	g_shell_dir = ft_strdup(cwd);
	free(cwd);
	manage_termios(save_config);
	grammar_file = ft_strjoin(g_shell_dir, grammar_file);
	if (!check_rights(grammar_file, F | R, false, true))
		exit(-1);
	grammar_init(grammar_file);
	setup_builtins();
	setup_variables_elements(environ);
	ht_new_table(&g_alias, 47, 65);
	ht_new_table(&g_hash, 47, 50);
	init_backgroundjobs();
	init_tcsettings();
	set_shlvl();
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
