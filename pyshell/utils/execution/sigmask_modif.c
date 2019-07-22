#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef NULL
# define NULL (void *) 0
#endif

int		change_sigmask(int signum, int action)
{
	sigset_t	set;

	sigemptyset(&set);
	sigaddset(&set, signum);
	return (sigprocmask(action, &set, NULL));
}

void	set_foreground(int pgid)
{
	int fd;

	fd = open("/dev/tty", O_RDWR);
	tcsetpgrp(fd, pgid);
}

int		cfork(int pgid, int background, int allow_background)
{
	int pid = fork();
	if (allow_background)
	{
		setpgid(pid, pgid);
		if (!background)
			set_foreground(pgid);
	}
	return (pid);
}
