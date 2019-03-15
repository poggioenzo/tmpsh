#include "screen_size.h"
#include <sys/ioctl.h>

void		screen_size(t_win *window)
{
	ioctl(0, TIOCGWINSZ, window);
}
