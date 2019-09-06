/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"
#include "file_rights.h"
#include "level_increment.h"
#include "builtins.h"
#include "termios_setter.h"
#include "grammar_init.h"
#include "variables.h"
#include "job_control.h"
#include "t_caps_utils.h"
#include "foreground.h"

int			g_last_status = 0;
pid_t		g_last_pid = 0;
t_pylst		*g_heredocs = NULL;
t_pylst		*g_passed_alias = NULL;
t_pylst		*g_actual_alias = NULL;
int			g_aliasindepth = 0;
char		g_last_char[5];

void		setup_globals(char **environ)
{
	char	*grammar_file;
	char	*cwd;

	setup_freefct();
	setup_variables_elements(environ);
	grammar_file = "grammar.txt";
	cwd = getcwd(NULL, 0);
	g_shell_dir = ft_strdup(cwd);
	free(cwd);
	manage_termios(save_config);
	grammar_file = ft_filejoin(&g_shell_dir, &grammar_file, false, false);
	if (!check_rights(grammar_file, F | R, false, true))
		exit(-1);
	grammar_init(grammar_file);
	setup_builtins();
	alloc_capabilities_struct();
	ht_new_table(&g_alias, 47, 65);
	ht_new_table(&g_hash, 47, 50);
	init_backgroundjobs();
	init_tcsettings();
	set_shlvl();
}

void		remove_globals(void)
{
	ft_strdel(&g_shell_dir);
	free_hash_table(&g_variables, 0);
	free_hash_table(&g_builtins, 0);
	free_str_array(&g_environ, 0);
	free_hash_table(&g_alias, 0);
	free_hash_table(&g_hash, 0);
	free_pylst(&g_jobs->list_jobs, 0);
	ft_memdel((void **)&g_jobs);
	ft_memdel((void **)&g_caps);
	free_grammar();
}
