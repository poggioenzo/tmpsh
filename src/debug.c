#include "debug.h"
#include "libft.h"

void		DEBUG_print_char(t_char *char_lst, int fd)
{
	ft_dprintf(fd_debug, "%p : ", char_lst);
	while (char_lst)
	{
		ft_dprintf(fd, "(%c, %d, %d)-->", char_lst->letter,\
				char_lst->position, char_lst->lock);
		char_lst = char_lst->next;
	}
	ft_dprintf(fd_debug, "NULL\n");
}

void		DEBUG_print_line(t_line *shell_lines, int fd)
{
	t_char	*char_lst;

	while (shell_lines)
	{
		char_lst = shell_lines->chars;
		ft_dprintf(fd, "%d =>", shell_lines->position);
		while (char_lst)
		{
			ft_dprintf(fd, "(%c, %d, %d)-->", char_lst->letter, char_lst->position,
					char_lst->lock);
			char_lst = char_lst->next;
		}
		ft_dprintf(fd, "NULL\n");
		shell_lines = shell_lines->next;
	}
}
