#include "t_caps_utils.h"
#include "libft.h"

/*
** alloc_capabilities_struct:
**
** Allocate a t_caps * element, prepare all termcaps strings in different
** attribute of our structure.
*/

int			alloc_capabilities_struct(t_caps **capabilities)
{
	if (tgetent(getenv("TERM"), NULL) == -1)
		return (0);
	if (!(*capabilities = (t_caps *)malloc(sizeof(t_caps))))
		return (MALLOC_ERROR);
	(*capabilities)->clear = tgetstr("cl", NULL);
	(*capabilities)->video = tgetstr("mr", NULL);
	(*capabilities)->reset_video = tgetstr("me", NULL);
	(*capabilities)->hide_cursor = tgetstr("vi", NULL);
	(*capabilities)->reset_cursor = tgetstr("ve", NULL);
	(*capabilities)->save_pos = tgetstr("sc", NULL);
	(*capabilities)->reset_pos = tgetstr("rc", NULL);
	(*capabilities)->del_line = tgetstr("dl", NULL);
	(*capabilities)->start_line = tgetstr("cr", NULL);
	(*capabilities)->move_up = tgetstr("up", NULL);
	(*capabilities)->move_down = tgetstr("do", NULL);
	return (MALLOC_SUCCESS);
}

int			free_capabilities_struct(t_caps **capabilities, int status)
{
	FREE(*capabilities);
	*capabilities = NULL;
	return (status);
}
