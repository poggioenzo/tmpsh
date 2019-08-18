#include <signal.h>
#include <sys/wait.h>
#include "signal_handler.h"
#include "libft.h"
#include "display.h"
#include "termios_setter.h"
#include "t_char_utils.h"
#include "line_utils.h"
#include "shell_setup.h"
#include "foreground.h"

/*
** shell_interupt:
**
** When SIGINT is catched, clean up the t_line chained list content
** to keep a single empty line who will wait for commands.
*/

static void		shell_interupt(int status)
{
	t_line		*shell_repr;
	t_cursor	*cursor;
	pid_t		tpgid;

	UNUSED(status);
	tpgid = get_tpgid();
	//SHOULD I wait with WNOHANG or normally, can be intersting
	//to wait programs end, if the are doing some stuff before exiting?
	while (waitpid(-tpgid, NULL, WNOHANG) != -1)
		;
	manage_shell_repr(GET, &shell_repr, &cursor);
	*cursor = (t_cursor){.row = -1, .column = -1};
	display_shell(shell_repr, cursor, FALSE);
	ft_printf("\n");
	line_proper(shell_repr);
	free_t_line_lst(&shell_repr->next, 0);
	*cursor = (t_cursor){.row = 0, .column = char_lst_len(shell_repr->chars)};
	display_shell(shell_repr, cursor, TRUE);
}

/*
** shell_background:
**
** Prepare the configuration to be pushed in background.
** Print a last time the shell to show it without the cursor.
*/

static void		shell_background(int status)
{
	t_line		*shell_repr;
	t_cursor	fake_cursor;

	UNUSED(status);
	manage_shell_repr(GET, &shell_repr, NULL);
	fake_cursor = (t_cursor){.row = -1, .column = -1};
	display_shell(shell_repr, &fake_cursor, FALSE);
	ft_printf(g_caps->reset_cursor);
	manage_termios(RESET);
	signal(SIGTSTP, SIG_DFL);
	kill(getpid(), SIGTSTP);
}

/*
** shell_continue:
**
** Restore the prompt and the termios whenever SIGCONT is received.
*/

static void		shell_continue(int status)
{
	t_line		*shell_repr;
	t_cursor	*cursor;

	UNUSED(status);
	manage_shell_repr(GET, &shell_repr, &cursor);
	manage_termios(SETUP);
	ft_printf(g_caps->hide_cursor);
	display_shell(shell_repr, cursor, TRUE);
	signal(SIGTSTP, shell_background);
}

/*
** shell_reshape:
**
** Display again the shell whenever SIGWINCH is received.
*/

static void		shell_reshape(int status)
{
	t_line		*shell_repr;
	t_cursor	*cursor;

	UNUSED(status);
	manage_shell_repr(GET, &shell_repr, &cursor);
	display_shell(shell_repr, cursor, FALSE);
}

/*
** signal_setup:
**
** Link each signal to his corresponding signal handler.
*/

int				signal_setup(void)
{
	signal(SIGINT, shell_interupt);
	signal(SIGQUIT, shell_exit);
	signal(SIGTSTP, shell_background);
	signal(SIGCONT, shell_continue);
	signal(SIGWINCH, shell_reshape);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	return (0);
}
