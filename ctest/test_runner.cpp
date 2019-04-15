#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#include "libft.h"
#include "test_runner.h"

#define NUMBER_TEST		1

test_store		test_list[NUMBER_TEST + 1] = {
	{"simple_pylst", simple_pylst},
	NULL
};

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

int		main(int argc, char **argv)
{
	pid_t	pid;
	int		status;
	int		index;
	
	index = 0;
	while (index < NUMBER_TEST)
	{
		pid = fork();

		if (pid == 0)
		{
			ft_printf("%s : ", test_list[index].name);
			test_list[index].test();
		}
		else
		{
			waitpid(pid, &status, 0);
			signal_analysis(status);
		}
		ft_printf("\n");
		index++;
	}
	return (0);
}
