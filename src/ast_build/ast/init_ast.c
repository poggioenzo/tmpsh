/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_ast.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:40:58 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:41:23 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ast.h"

t_ast	*init_ast(t_tagstokens *tgtk)
{
	t_ast	*self;

	self = (t_ast*)ft_memalloc(sizeof(t_ast));
	self->list_branch = NULL;
	self->type = "ROOT";
	self->link_fd = 0;
	self->pid = -1;
	self->command = str_command_tagstokens(tgtk);
	self->print = NULL;
	self->complete = FALSE;
	split_branch_ast(self, tgtk);
	update_length_tagstokens(tgtk);
	return (self);
}
