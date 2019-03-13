#include "screen_size.h"

int			screen_size(int *col, int *line)
{
	struct winsize window;

	ioctl(0, TIOCGWINSZ, &window);
	*line = window.ws_row;
	*col = window.ws_col;
	return (1);
}
