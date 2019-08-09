#include <sys/wait.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	int pid = 0;

	pid = waitpid(55555, NULL, 0);
	if (pid == -1)
		printf("Error pid\n");
}
