#ifndef TMPSH_H
# define TMPSH_H

# include <unistd.h>
# include "libft.h"
# ifndef UNUSED_VAR
#  define UNUSED_VAR
#  define UNUSED(variable) (void) variable
# endif

# define NAME_SH "bash:"
# define RC_FILE ".tmpshrc"

# include "styles.h"

# define DF ft_printf(PURPLE"%s\n"WHITE, __func__)
# define DFE ft_printf(YELLOW"%s\n"WHITE, __func__)
# define DFT ft_printf(GREEN"%s\n"WHITE, __func__)
# define DFF ft_printf(RED"%s\n"WHITE, __func__)
# define DFB ft_printf(BLUE"%s\n"WHITE, __func__)
# define NOT_USE(arg) __attribute__((unused))arg

# ifndef NULL
#  define NULL (void *) 0
# endif

/*
** Cursor structur
*/

typedef	struct
{
	short	row;
	short	column;
}			t_cursor;

/*
** t_char and t_line : structures to represent the shell.
*/

typedef struct s_char	t_char;

struct		s_char
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

typedef struct s_caps	t_caps;

struct		s_caps
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
};

# undef false
# undef true
# undef stdout
# undef stdin

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

struct		s_hist
{
	char	*line;
	short	is_tmp;
	t_hist	*next;
	t_hist	*prev;
};

/*
** Grammar struct
*/

typedef struct s_grammar	t_grammar;

struct		s_grammar
{
	char		*path;
	t_ht_table	*grammar;
	t_ht_table	*reverse;
	t_pylst		*reverse_list;
	char		*spaces;
	char		*escape;
	t_ht_table	*opening_tags;
	t_ht_table	*dquotes_opening_tags;
	int			maxlen_leaf_op;
	t_pylst		*leaf_op;
};

/*
** Structs for the AbstractSyntaxTree
*/

typedef struct s_tagstokens		t_tagstokens;
struct		s_tagstokens
{
	t_pylst		*tokens;
	t_pylst		*tags;
	t_pylst		*stack;
	char		*token_error;
	t_bool		valid;
	t_bool		incomplete;
	t_bool		not_heredocs;
	size_t		length;
	int			iter;
};

typedef struct s_ast	t_ast;
struct		s_ast
{
	t_pylst		*list_branch;
	char		*type;
	int			link_fd;
	pid_t		pid;
	char		*command;
	t_bool		complete;
};

typedef struct s_acb	t_acb;
struct		s_acb
{
	t_tagstokens	*tagstokens;
	char			*begin_andor;
	char			*tag_end;
	t_pylst			*subast;
	t_pylst			*subcmd_type;
	t_pylst			*redirectionfd;
	char			*command;
	char			*print;
	int				stdin;
	int				stdout;
	t_bool			background;
	int				status;
	pid_t			pid;
	pid_t			pgid;
	t_bool			complete;
	t_bool			running;
};

typedef struct s_redirection_fd		t_redirection_fd;
struct		s_redirection_fd
{
	t_tagstokens	*tagstokens;
	char			*type;
	int				source;
	char			*print;
	void			*dest;
	t_ast			*heredoc_ast;
	t_bool			close;
	t_bool			error;
};

typedef struct s_tags_tokens_monitor	t_tags_tokens_monitor;
struct		s_tags_tokens_monitor
{
	t_tagstokens	*tt;
	int				i;
	char			*tag;
	char			*token;
	t_bool			begin_cmd;
	t_pylst			*heredocs_keys;
	t_pylst			*opened;
};

typedef struct s_heredocs	t_heredocs;
struct		s_heredocs
{
	char			*key;
	int				quoted;//Check type
	int				len_key;
	t_bool			minus;
	t_bool			closed;
	t_tagstokens	*tagstokens;
	t_pylst			*stack;
	t_bool			in_cmdsubst;
};

/*
** Background jobs
*/

enum	e_waitstate
{
	finish = 0,
	running = 1,
};

typedef struct s_job	t_job;
struct		s_job
{
	t_pylst			*branches;
	int				number;
	pid_t			pgid;
	char			*command;
};

typedef struct s_background_job		t_background_job;
struct		s_background_job
{
	t_pylst		*list_jobs;
	t_bool		allow_background;
};

typedef struct s_hash_exec	t_hash_exec;
struct		s_hash_exec
{
	char	*exec_file;
	int		count;
};

/*
** Debug functions
*/

void		DEBUG_print_line(t_line *shell_lines, int fd);
int			fd_debug;
void		show_history(t_hist *history);
void		DEBUG_cursor(t_cursor *cursor, int fd);

# include "debug.h"
# include "globals.h"

#endif
