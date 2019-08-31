/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_ast.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:38:24 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/31 16:36:41 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ast.h"
#include "acb.h"

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

void	free_ast_type(void *ast)
{
	free_ast((t_ast **)ast);
}
