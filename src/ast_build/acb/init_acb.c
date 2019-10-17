/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_acb.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:31:38 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:32:32 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

t_acb	*init_acb(t_tagstokens *tgtk, char *begin_andor, char *tag_end)
{
	t_acb	*self;

	self = (t_acb*)ft_memalloc(sizeof(t_acb));
	self->tagstokens = tgtk;
	self->begin_andor = begin_andor;
	self->tag_end = "";
	if (in_grammar(tag_end, "ABS_TERMINATOR"))
		self->tag_end = tag_end;
	self->stdin = -1;
	self->stdout = -1;
	self->status = -1;
	self->pid = -1;
	self->command = str_command_tagstokens(tgtk);
	check_subast_acb(self);
	set_subast_type_acb(self);
	check_redirection_acb(self);
	self->print = str_command_tagstokens(tgtk);
	return (self);
}
