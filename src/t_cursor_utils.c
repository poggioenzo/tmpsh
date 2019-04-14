#include "t_cursor_utils.h"
# include "libft.h"
# include "t_caps_utils.h"

int		alloc_cursor(t_cursor **cursor)
{
	if (!(*cursor = (t_cursor *)MALLOC(sizeof(t_cursor))))
		return (MALLOC_ERROR);
	(*cursor)->row = 0;
	(*cursor)->column = 0;
	return (MALLOC_SUCCESS);
}

int		dealloc_cursor(t_cursor **cursor, int status)
{
	FREE(*cursor);
	*cursor = NULL;
	return (status);
}

void	show_cursor(char letter)
{
	ft_printf("%s%c%s", g_caps->video, letter, g_caps->reset_video);
}
