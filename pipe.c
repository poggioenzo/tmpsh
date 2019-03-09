#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int		display_error(char *err_msg, int status)
{
	perror(err_msg);
	return (status);
}

int		main(int argc, char **argv, char **environ)
{
	int		fd_pipe[2];
	char	*argv_grep[] = {"/bin/grep", "zsh", NULL};
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		return (display_error("pipe", 1));
    
	if ((pid = fork()) == -1)
		return (display_error("fork", 1));
	if (pid == 0)
	{
		printf("top run in background\n");
		dup2(fd_pipe[1], 1);
		execve("/usr/bin/top", argv, environ);
	}
	else
	{
		dup2(fd_pipe[0], 0);
		printf("run grep\n");
		execve("/usr/bin/grep", argv_grep, environ);
	}
  return (0);
}
