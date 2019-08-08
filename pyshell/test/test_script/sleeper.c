#include <signal.h>
#include <unistd.h>
#include <stdio.h>

char *name;

void	handler(int signum)
{
    printf("%s: Handle signal %d\n", name, signum);
    signal(signum, SIG_DFL);
    sleep(1);
    printf("KILLING\n");
    if (kill(getpid(), signum) == -1)
		perror("kill");
    printf("out\n");
}

int		main(int argc, char **argv)
{
	name = argv[0];
	printf("Start : %s\n", argv[0]);
	signal(SIGTSTP, handler);
	pause();
	printf("end\n");

}
