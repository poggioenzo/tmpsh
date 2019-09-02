#ifndef SCREEN_SIZE_H
# define SCREEN_SIZE_H

# include <sys/ioctl.h>

typedef struct winsize	t_win;

void		screen_size(t_win *window);

#endif
