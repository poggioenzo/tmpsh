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
