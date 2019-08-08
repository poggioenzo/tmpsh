#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


#define SIGNAL_STR(var, signal)	if (var == signal) signal_str = #signal;

void	interrupt_handler(int signum)
{
	char *signal_str = "";

	SIGNAL_STR(signum, SIGTSTP);
	SIGNAL_STR(signum, SIGCONT);
	printf("Father catched %s.\n", signal_str);
	signal(signum, SIG_DFL);
	kill(getpid(), signum);
}

void	show_tab(char **array)
{
	while (*array)
		printf("%s\n", *array++);
}

void	run_child(char **argv, char **environ)
{
	char *execname = argv[1];
	char **args_exec = argv + 1;

	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	setpgid(0, 0);
	tcsetpgrp(0, getpgrp());
	if (execve(execname, args_exec, environ) == -1)
		perror("execve");
}

void	error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

char	*read_line(void)
{
	char buffer[250];
	int ret;

	ret = read(0, buffer, 249);
	buffer[ret] = 0;
	printf("%s", buffer);
	return (NULL);
}

void	init_shell(void)
{
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTTIN, SIG_IGN);
	signal (SIGTTOU, SIG_IGN);
	signal (SIGCHLD, SIG_IGN);
}

 /*
 ** Fork a process a pull it in background by changing his process group id (pgid).
 ** Wait a while with the father, restore de children in the foreground process group (with tcsetgrp)
 ** and send him SIGCONT.
 */


int		main(int argc, char **argv, char **environ)
{
	pid_t pid;
	char *argv_prog[] = {"top",  NULL};
	char *ps_argv[] = {"ps", "-au", "simrossi", "-o", "user,command,pgid,gid,tpgid", NULL};
	int		status;
	int term_sig;
	int return_val;

	if (argc == 1)
		error("No args.");
	init_shell();
	if ((pid = fork()) == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		run_child(argv, environ);
	}
	else
	{
		setpgid(pid, 0);
		tcsetpgrp(0, pid);
		printf("Father starting wait.\n");
		waitpid(pid, &status, WUNTRACED);
		printf("Father end wait.\n");
		sleep(2);
		printf("end father sleep\n");
		tcsetpgrp(0, getpgrp());
		read_line();
		return_val = WEXITSTATUS(status);
		term_sig = WSTOPSIG(status);
		if (term_sig == SIGTSTP)
		{
			sleep(3);
			printf("Yolo\n");
		}
	}
	return (0);
}
