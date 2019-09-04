/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   routine_tagstokens.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/04 16:42:44 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 16:43:20 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

void	routine_tagstokens(t_tagstokens **self, char *shell_content)
{
	free_pylst(&g_actual_alias, 42);
	free_pylst(&g_passed_alias, 42);
	free_pylst(&g_heredocs, 42);
	g_aliasindepth = 0;
	input_init_tagstokens(self, shell_content);
}
