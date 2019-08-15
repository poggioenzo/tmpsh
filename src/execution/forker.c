#include "tmpsh.h"
#include "libft.h"
#include "foreground.h"

int		fork_prepare(int pgid, t_bool background)
{
	pid_t pid;

	pid = fork();
	if (g_jobs->allow_background == true)
	{
		setpgid(pid, pgid);
		if (background == false)
			set_foreground(getpgid(pid));
	}
	return (pid);
}
