#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#include "libft.h"
#include "test_runner.h"

#define NUMBER_TEST		18

test_store		test_list[NUMBER_TEST + 1] = {
	{"simple_chare_pylst", simple_chare_pylst},
	{"simple_int_pylst", simple_int_pylst},
	{"multitype_pylst", multitype_pylst},
	{"hash_creation", hash_creation},
	{"hash_single_insert", hash_single_insert},
	{"hash_multiple_insert", hash_multiple_insert},
	{"hash_insert_single_alveol", hash_insert_single_alveol},
	{"hash_multitype_insert", hash_multitype_insert},
	{"hash_single_delete", hash_single_delete},
	{"hash_multiple_delete", hash_multiple_delete},
	{"hash_alveol_deletion", hash_alveol_deletion},
	{"t_line_allocation", t_line_allocation},
	{"t_line_lst_allocation", t_line_lst_allocation},
	{"t_line_longer_lst", t_line_longer_lst},
	{"t_line_len", t_line_len},
	{"t_line_update_test", t_line_update_test},
	{"t_line_get_last_test", t_line_get_last_test},
	{"t_line_extract_test_simple", t_line_extract_test_simple},
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
	
	setup_freefct();
	index = 0;
	while (index < NUMBER_TEST)
	{
		pid = fork();

		if (pid == 0)
		{
			ft_printf("%-30s : ", test_list[index].name);
			test_list[index].test();
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
