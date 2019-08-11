/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tmpsh.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 14:40:22 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 20:30:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TMPSH_H
# define TMPSH_H


# ifndef UNUSED_VAR
#  define UNUSED_VAR
#  define UNUSED(variable)	(void) variable
# endif


# ifndef NULL
#  define NULL (void *) 0
# endif

/*
** Useful structs prototype from libft
*/
typedef struct s_pylst	t_pylst;
typedef struct s_ht_table	t_ht_table;
typedef signed int			pid_t;


enum	e_newline {leave_check = 2, invalid_syntax, not_nested};

typedef struct s_operand	t_operand;

struct s_operand
{
	char		open_char;
	int			type:6;
	t_operand	*next;
};

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
char		g_last_char[5];

enum	malloc_fail
{
	MALLOC_ERROR = 0,
	MALLOC_SUCCESS = 1
};

typedef enum
{
	false = 0,
	true = 1,
}	t_bool;

# define TRUE		1
# define FALSE		0

# define SUCCESS	1
# define FAILURE	0

# define STORE		3
# define GET		2
# define GO_FREE	1
# define CREATE		0

/*
** History management.
*/

# define HISTORY_FILE	"~/.tmpsh_history"

typedef struct s_hist	t_hist;

# define STORED		0b1

struct s_hist
{
	char	*line;
	short	is_tmp;
	t_hist	*next;
	t_hist	*prev;
};

/*
** Grammar structs
*/


// Both structure t_grammar and t_shellgrammar can be joined togethercan be
// joined together
typedef struct
{
	char *path;
	t_ht_table	*grammar;
	t_ht_table	*reverse;
}		t_grammar2;

typedef struct
{
	t_pylst		*spaces;
	char		escape;
	t_ht_table	*opening_tags;
	t_ht_table	*dquotes_opening_tags;
	int			maxlen_leaf_op;
}		t_shellgrammar;

typedef struct
{
	char *path;
	t_ht_table	*grammar;
	t_ht_table	*reverse;
	t_pylst		*spaces;
	char		escape;
	t_ht_table	*opening_tags;
	t_ht_table	*dquotes_opening_tags;
	int			maxlen_leaf_op;
	t_pylst		*leaf_op;
}		t_grammar;

/*
** Structs for the AbstractSyntaxTree
*/

typedef struct
{
	t_pylst		*heredocs;
	t_pylst		*tokens;
	t_pylst		*tags;
	t_pylst		*stack;
	char		*token_error;
	t_bool		valid;
	t_bool		incomplete;
	int			length;
}			t_tagstokens;

typedef struct
{
	t_pylst		*list_branch;
	char		*type;
	int			link_fd;
	pid_t		pid;
	char		*command;
	t_bool		complete;
}			t_ast;

typedef struct
{
	t_tagstokens	tagstokens;
	char			*begin_andor;
	char			*tag_end;
	t_pylst			*subast;
	t_pylst			*subcmd_type;
	t_pylst			*redirectionfd;
	char			*command;
	int				stdin;
	int				stdout;
	t_bool			background;
	int				status;
	pid_t			pid;
	pid_t			pgid;
	t_bool			complete;
}			t_acb;

typedef struct
{
	t_tagstokens	tagstokens;
	char			*type;
	int				source;
	char			*dest;
	t_bool			close;
	t_bool			error;
}		t_redirection_fd;

typedef struct
{
	t_tagstokens	tt;
	int				i;
	char			*tag;
	char			*token;
	t_bool			begin_cmd;
	t_pylst			*heredocs_keys;
	t_pylst			*opened;
}	t_tags_tokens_monitor;

/*
** Background jobs
*/

enum	waitstate
{
	finish = 0,
	running = 1,
};

typedef struct
{
	t_pylst		*list_jobs;
	t_bool		allow_background;
}	t_background_job;

/*
** Debug functions
*/

void		DEBUG_print_line(t_line *shell_lines, int fd);
int		fd_debug;
void	show_history(t_hist *history);


#include "debug.h"
# include "globals.h"

#endif
