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
#include "char_concatenation.h"
#include "display.h"
#include "run_ast.h"
#include "shell_setup.h"
#include "history.h"
#include "line_extend.h"
#include "ast.h"
#include "tagstokens.h"

#include "termios_setter.h"

/*
** register_command:
**
** Whenever a new command is send, store it to the current history and rewrite
** the history file.
*/

static void	register_command(char *shell_str)
{
	t_hist	*history;
	char	*shell_cpy;
	int		store_history;

	history_store(GET, &history);
	store_history = !history ? TRUE : FALSE;
	if (!(shell_cpy = ft_strdup(shell_str)))
		exit(-1);
	if (shell_cpy[0])
	{
		rstrip(shell_cpy);
		push_t_hist(&history, shell_cpy, FALSE);
		rewrite_history(history);
	}
	else
		ft_strdel(&shell_cpy);
	if (store_history)
		history_store(STORE, &history);
}

void		execute_tagstoken(t_tagstokens *tagstokens, char *command)
{
	ft_printf(g_caps->reset_cursor);
	rstrip(command);
	if (ft_strlen(command) > 0 && command[0] != ' ')
		register_command(command);
	manage_termios(remove_config);
	executor(init_ast(tagstokens));
	manage_termios(shell_config);
	ft_printf(g_caps->hide_cursor);
}

/*
** newline_check:
**
** Whenever a newline is found, check if the current shell is nested or not,
** a new line will be created according to the result.
*/

int			newline_check(t_line **shell_repr, t_cursor **cursor)
{
	t_tagstokens	*tagstoken;
	char			*shell_content;

	shell_content = render_shell_content(*shell_repr);
	routine_tagstokens(&tagstoken, shell_content);
	if (tagstoken->incomplete && tagstoken->valid)
	{
		add_new_line(*shell_repr, tagstoken, *cursor);
		free_tagstokens(&tagstoken, 0);
		ft_strdel(&shell_content);
		return (true);
	}
	**cursor = (t_cursor){.row = -1, .column = -1};
	display_shell(*shell_repr, *cursor, false);
	ft_printf("\n");
	manage_shell_repr(GO_FREE, NULL, NULL);
	if (tagstoken->valid && !tagstoken->incomplete)
		execute_tagstoken(tagstoken, shell_content);
	else
		ft_dprintf(2, NAME_SH" syntax error near %s\n", tagstoken->token_error);
	shell_preconfig(shell_repr, cursor);
	ft_strdel(&shell_content);
	free_tagstokens(&tagstoken, 0);
	return (false);
}
