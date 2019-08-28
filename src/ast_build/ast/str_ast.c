/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_ast.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 19:49:50 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 19:50:19 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ast.h"

/*
** str_ast:
**
** description:
** Create and return string repredentation of an ast.
**
** parameter:
** - (t_ast *) self : the actual abstract syntax tree.
**
** return value:
** - (char *) str : string repredentation of an ast.
*/

char	*str_ast(t_ast *self)
{
	char	*str;
	char	*string_acb;
	t_acb	*value;

	str = ft_strnew(0);
	string_acb = ft_strnew(0);
	str = free_join(str, YELLOW, FALSE);
	str = free_join(str, self->type ? self->type : "NONE", FALSE);
	str = free_join(str, "\n  ", FALSE);
	str = free_join(str, WHITE, FALSE);
	while (iter_pylst(self->list_branch, (void **)&value))
		string_acb = free_join(string_acb, str_acb(value), TRUE);
	string_acb = split_shift(&string_acb);
	str = free_join(str, string_acb, TRUE);
	return (str);
}
