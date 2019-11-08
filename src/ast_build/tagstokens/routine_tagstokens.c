/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   routine_tagstokens.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/04 16:42:44 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:56:46 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"
#include "ttm.h"

static void	remove_comments_newline(char *str)
{
	int		escaped;
	char 	*save_str;

	escaped = false;
	save_str = str;
	while (*str)
	{
		if (*str == '\\' && escaped == false)
			escaped = true;
		else
		{
			if (*str == '\'' && escaped == false
				&& !(str = ft_strchr(str + 1, '\'')))
				return ;
			else if (*str == '\n' && escaped == true && str[1])
			{
				ft_strcpy(str - 1, str + 1);
				remove_comments_newline(save_str);
				return ;
			}
			escaped = false;
		}
		str++;
	}
}


void		reset_routine(void)
{
	t_tags_tokens_monitor *self;

	self = NULL;
	is_newline_ttm(self, true);
	free_pylst(&g_actual_alias, 42);
	free_pylst(&g_passed_alias, 42);
	free_pylst(&g_heredocs, 42);
	g_aliasindepth = 0;
}

void		routine_tagstokens(t_tagstokens **self, char *shell_content)
{
	remove_comments_newline(shell_content);
	reset_routine();
	input_init_tagstokens(self, shell_content);
	if ((*self)->incomplete || !(*self)->valid)
		reset_routine();
}
