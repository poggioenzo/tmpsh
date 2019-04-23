#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#include "libft.h"
#include "test_runner.h"

#define ADD_TEST(test_name)	g_tests[__COUNTER__] = (test_store){.name = #test_name, .test = test_name}

test_store	*g_tests = NULL;
int		total_tests;

/*
** fill_tests_functions:
**
** Add each test function to the list of test.
** Each function must be added with the ADD_TEST macro:
** 
** example:
** ADD_TEST(my_new_test);
*/

void	fill_tests_functions(void)
{
	ADD_TEST(simple_chare_pylst);
	ADD_TEST(simple_int_pylst);
	ADD_TEST(multitype_pylst);
	ADD_TEST(hash_creation);
	ADD_TEST(hash_single_insert);
	ADD_TEST(hash_multiple_insert);
	ADD_TEST(hash_insert_single_alveol);
	ADD_TEST(hash_multitype_insert);
	ADD_TEST(hash_single_delete);
	ADD_TEST(hash_multiple_delete);
	ADD_TEST(hash_alveol_deletion);
	ADD_TEST(t_line_allocation);
	ADD_TEST(t_line_lst_allocation);
	ADD_TEST(t_line_longer_lst);
	ADD_TEST(t_line_len);
	ADD_TEST(t_line_update_test);
	ADD_TEST(t_line_get_last_test);
	ADD_TEST(t_line_extract_test_simple);
}

/*
** function_init:
**
** Store in the first time the number of tests using __COUNTER__ macro.
** Allocate after the g_test variable according to the number of tests.
*/
void	function_init(void)
{
	total_tests = __COUNTER__;
	g_tests = (test_store *)malloc(sizeof(test_store) * total_tests);
	fill_tests_functions();
}

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
