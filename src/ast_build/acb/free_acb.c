/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_acb.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/31 16:33:32 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/31 16:34:30 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "acb.h"

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

void	free_acb_type(void *acb)
{
	free_acb((t_acb **)acb);
}
