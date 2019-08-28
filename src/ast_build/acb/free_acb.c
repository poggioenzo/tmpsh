
#include "acb.h"

// typedef struct
// {
// 	t_tagstokens	*tagstokens;
// 	char			*begin_andor; <- dont free grammar ptr
// 	char			*tag_end; <- dont free grammar ptr
// 	t_pylst			*subast;
// 	t_pylst			*subcmd_type;
// 	t_pylst			*redirectionfd;
// 	char			*command;
// 	char			*print;
// 	int				stdin;
// 	int				stdout;
// 	t_bool			background;
// 	int				status;
// 	pid_t			pid;
// 	pid_t			pgid;
// 	t_bool			complete;
// }			t_acb;

void	free_acb(t_acb **self)
{
	if (self && *self)
	{
		free_tagstokens(&(*self)->tagstokens, 42);
		free_pylst(&(*self)->subast, 42);
		free_pylst(&(*self)->subcmd_type, 42);
		free_pylst(&(*self)->redirectionfd, 42);
		if ((*self)->command)
			ft_strdel(&(*self)->command);
		if ((*self)->print)
			ft_strdel(&(*self)->print);
		ft_memdel((void **)self);
	}
}

void free_acb_type(void *acb)
{
	free_acb((t_acb **) acb);
}
