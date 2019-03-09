#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int		main(int argc, char **argv, char **environ)
{
	pid_t pid;
	pid_t pgid;
	char *argv_prog[] = {"cat", argv[1],  NULL};
	int		status;
	pid_t control;

	pid = tcgetpgrp(1);
	printf("pid tcgetpgrp : %d\n", pid);
	sleep(3);

	if ((pid = fork()) == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		setpgid(0, 0);
		if (execve("/usr/bin/top", argv_prog, environ) == -1)
			perror("execve");
	}
	else
	{
		int		wait_time = 5;
		printf("father sleep for %d sec\n", wait_time);
		sleep(wait_time);
		tcsetpgrp(0, pid);
		kill(pid, SIGCONT);
		waitpid(pid, &status, 0);
	}
	return (0);
}
