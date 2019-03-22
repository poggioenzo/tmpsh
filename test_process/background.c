#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>


/*
** Fork a process a pull it in background by changing his process group id (pgid).
** Wait a while with the father, restore de children in the foreground process group (with tcsetgrp)
** and send him SIGCONT.
*/

int		main(int argc, char **argv, char **environ)
{
	pid_t pid;
	pid_t pgid;
	char *argv_prog[] = { "" ,"$PATH",  NULL};
	int		status;
	pid_t control;

	pid = tcgetpgrp(1);
	printf("pid tcgetpgrp : %d\n", pid);
	sleep(0);

	if ((pid = fork()) == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		setpgid(0, 0);
		if (execve("/bin/echo", argv_prog , NULL) == -1)
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
