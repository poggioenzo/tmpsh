#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#include "libft.h"
#include "test_runner.h"


test_store	*g_tests = NULL;
int			total_tests = 0;


int		main(int argc, char **argv)
{
	pid_t	pid;
	int		status;
	int		index;
	
	function_init();
	setup_freefct();
	index = 0;
	while (index < total_tests)
	{
		pid = fork();

		if (pid == 0)
		{
			ft_printf("%-30s : ", g_tests[index].name);
			g_tests[index].test();
			error_display();
			exit(0);
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
