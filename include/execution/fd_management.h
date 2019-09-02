#ifndef FD_MANAGEMENT_H
# define FD_MANAGEMENT_H

enum	e_save_fd
{
	save,
	restore,
};

void	replace_fd(int expected_fd, int old_fd);
int		setup_pipe_fd(int pipes_fd[2]);
void	save_std_fd(enum e_save_fd mode);
void	replace_std_fd(int stdin, int stdout);

#endif
