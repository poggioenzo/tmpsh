#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "tmpsh.h"
#include "fd_management.h"

/*
** digit_string:
**
** Check if the given string contain only digits.
*/

static int		digit_string(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

/*
** need_open_file:
**
** Check according to the redirection type if a file have to be open.
*/

static int		need_open_file(char *type)
{
	return (ft_strequ(type, "TRUNC") || ft_strequ(type, "APPEND") || \
			ft_strequ(type, "READ_FROM"));
}

/*
** convert_dest:
**
** Retrieve the int value of the string redirection->dest.
*/

static void		convert_dest(t_redirection_fd *redirection)
{
	int		dest_fd;

	if (digit_string(redirection->dest))
	{
		dest_fd = ft_atoi(redirection->dest);
		redirection->dest = &dest_fd;
	}
	else
		redirection->dest = NULL;
}

/*
** open_redirection_file:
**
** For a given redirection, open the destination file with
** the expected mode.
*/

void			open_redirection_file(t_redirection_fd *redirection)
{
	int		fd;
	int		flags;

	if (need_open_file(redirection->type))
	{
		flags = 0;
		if (access(redirection->dest, F_OK) == -1)
			flags |= O_CREAT;
		if (ft_strequ(redirection->type, "TRUNC"))
			flags |= O_WRONLY;
		else if (ft_strequ(redirection->type, "APPEND"))
			flags |= O_WRONLY | O_APPEND;
		else if (ft_strequ(redirection->type, "READ_FROM"))
			flags |= O_RDONLY;
		if ((fd = open(redirection->dest, flags, 0666)) != -1)
			redirection->dest = &fd;
		else
		{
			ft_dprintf(STDERR_FILENO, "tmpsh: permission denied: %s\n", \
					redirection->dest);
			redirection->error = true;
		}
	}
	else
		convert_dest(redirection);
}
