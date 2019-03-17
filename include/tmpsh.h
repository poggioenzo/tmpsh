#ifndef TMPSH_H
# define TMPSH_H

#define UNUSED(x) (void) x
#define ft_getenv(var)	getenv(var)

/*
** Cursor structure
*/

typedef	struct
{
	short	row;
	short	column;
}		t_cursor;

/*
** t_char and t_line : structures to represent the shell.
*/

typedef struct s_char	t_char;

struct	s_char
{
	char		letter;
	short		lock:2;
	short		position;
	t_char		*next;
};

typedef struct s_line	t_line;

struct		s_line
{
	int			position;
	t_char		*chars;
	t_line		*next;
};


/*
** structure to store termcap capabilities
*/

typedef struct	s_caps
{
	char	*clear;
	char	*video;
	char	*reset_video;
	char	*hide_cursor;
	char	*reset_cursor;
	char	*save_pos;
	char	*reset_pos;
	char	*del_line;
	char	*start_line;
	char	*move_up;
	char	*move_down;
}				t_caps;

t_caps		*g_caps;

enum	malloc_fail
{
	MALLOC_ERROR = 0,
	MALLOC_SUCCESS = 1
};

# define TRUE	1
# define FALSE	0
# define SUCCESS	1
# define FAILURE	0

/*
** History management.
*/

#define HISTORY_FILE	"~/.tmpsh_history"

typedef struct s_hist	t_hist;

struct s_hist
{
	char	*line;
	t_hist	*next;
	t_hist	*prev;
};

/*
** Debug functions
*/

void		DEBUG_print_line(t_line *shell_lines, int fd);
extern int		fd_debug;


#include "debug.h"

#endif