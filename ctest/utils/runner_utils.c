#include "libft.h"
#include "test_runner.h"
#include <sys/wait.h>

void	display(char letter, char *color)
{
	ft_printf("%s%c%s", color, letter, RESET);
}

void	signal_analysis(int status)
{
	int		exit_status;
	int		kill_signal;

	if (WIFSIGNALED(status))
	{
		kill_signal = WTERMSIG(status);
		if (kill_signal == SIGSEGV)
			display('S', RED);
		else if (kill_signal == SIGABRT)
			display('A', RED);
		else if (kill_signal == SIGABRT)
			display('X', RED);
	}
}
