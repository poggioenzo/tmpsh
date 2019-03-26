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
void		DEBUG_operand_lst(t_operand *operand_list)
{
	if (!operand_list)
		ft_dprintf(fd_debug, "NO OPERAND IN LIST\n");
	else
	{
		while (operand_list)
		{
			ft_dprintf(fd_debug, "{operand :%d}-->", operand_list->type);
			operand_list = operand_list->next;
		}
		ft_dprintf(fd_debug, "NULL\n");
	}
}
void	DEBUG_history(t_hist *history)
{
	while (history)
	{
		ft_dprintf(fd_debug, "addresses : %p   | prev : %p | len : %d\n", history, history->prev, 
				ft_strlen(history->line));
		ft_dprintf(fd_debug, "line : %s|\n", history->line);
		history = history->next;
	}
}

