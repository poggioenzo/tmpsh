/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_ast.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:38:24 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:40:23 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ast.h"
#include "acb.h"

// typedef struct
// {
// 	t_pylst		*list_branch;
// 	char		*type; <-- don't free grammar ptr
// 	int			link_fd;
// 	pid_t		pid;
// 	char		*command;
// 	char		*print;
// 	t_bool		complete;
// }			t_ast;

void	free_ast(t_ast **self)
{
	if (self && *self)
	{
		free_pylst(&(*self)->list_branch, 42);
		if ((*self)->command)
			ft_strdel(&(*self)->command);
		ft_memdel((void **)self);
	}
}

void free_ast_type(void *ast)
{
	free_ast((t_ast **) ast);
}
