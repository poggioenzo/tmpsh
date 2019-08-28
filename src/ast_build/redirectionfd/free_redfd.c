
#include "redirectionfd.h"
#include "ast.h"

// typedef struct
// {
// 	t_tagstokens	*tagstokens;
// 	char			*type; <-- don't free grammar ptr
// 	int				source;
// 	char			*dest;
// 	char			*print;
// 	t_bool			close;
// 	t_bool			error;
// 	t_ast			*heredoc_ast;
// }				t_redirection_fd;

void free_redfd(t_redirection_fd **self)
{
	if (self && *self)
	{
		free_tagstokens(&(*self)->tagstokens, 42);
		if ((*self)->print)
			ft_strdel(&(*self)->print);
		if ((*self)->heredoc_ast)
			free_ast(&(*self)->heredoc_ast);
		ft_memdel((void **)self);
	}
}

void free_redfd_type(void *redfd)
{
	free_redfd((t_redirection_fd **) redfd);
}
