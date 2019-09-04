#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#include "libft.h"
#include "test_runner.h"
#include "globals_setup.h"


test_store	*g_tests = NULL;
int			total_tests = 0;

/*
** prepare_format:
**
** Function to prepare the string who will be used by
** printf to display test result.
** Get the maximum string length for all test
** and set it as a field.
**
** Return value:
** string like "%-Xs : ", with X as a variable.
*/

char	*prepare_format(void)
{
	int		max_len = 0;
	int		index = 0;
	int		new_len = 0;
	char	*format;
	char	*tmp_str;

	while (index < total_tests)
	{
		new_len = ft_strlen(g_tests[index].name);
		if (new_len > max_len)
			max_len = new_len;
		index++;
	}
	format = "%-";
	tmp_str = ft_itoa(max_len);
	format = ft_fstrjoin(&format, &tmp_str, 0, 1);
	tmp_str = "s : ";
	format = ft_fstrjoin(&format, &tmp_str, 1, 0);
	return (format);
}

/*
** main:
**
** Main loop to iterate over each test function.
** Fork himself in a first time to run the test in a subprocess.
** Wait the end of the child process and analyse the result,
** if it end due to a kill signal.
*/

int		main(int argc, char **argv, char **environ)
{
	pid_t	pid;
	int		status;
	int		index;
	char	*printf_format;
	
	function_init();
	setup_globals(environ);
	index = 0;
	printf_format = prepare_format();
	while (index < total_tests)
	{
		pid = fork();

		if (pid == 0)
		{
			ft_printf(printf_format, g_tests[index].name);
			g_tests[index].test();
			ft_printf("\n");
			error_display();
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			signal_analysis(status);
		}
		index++;
	}
	return (0);
}
